
/** @file
 * Process Incoming and outgoing serial communications.
 */

#include <Arduino.h>
#include "comms.h"
#include "FastCRC.h"
#include "pages.h"

// Forward declarations

/** @brief Processes a message once it has been fully received */
void processSerialCommand(void);

#define SERIAL_RC_OK 0x00       //!< Success
#define SERIAL_RC_REALTIME 0x01 //!< Unused
#define SERIAL_RC_PAGE 0x02     //!< Unused

#define SERIAL_RC_BURN_OK 0x04 //!< EEPROM write succeeded

#define SERIAL_RC_TIMEOUT 0x80   //!< Timeout error
#define SERIAL_RC_CRC_ERR 0x82   //!< CRC mismatch
#define SERIAL_RC_UKWN_ERR 0x83  //!< Unknown command
#define SERIAL_RC_RANGE_ERR 0x84 //!< Incorrect range. TS will not retry command
#define SERIAL_RC_BUSY_ERR 0x85  //!< TS will wait and retry

#define SERIAL_LEN_SIZE 2U
#define SERIAL_TIMEOUT 3000 // ms

#define SEND_OUTPUT_CHANNELS 48U

#define SERIAL_BUFFER_SIZE 517
#define LOG_ENTRY_SIZE 127
#define BLOCKING_FACTOR 121
#define TABLE_BLOCKING_FACTOR 64

bool firstCommsRequest = true; /**< The number of times the A command has been issued. This is used to track whether a reset has recently been performed on the controller */
volatile byte secl;
uint32_t deferEEPROMWritesUntil = 0;
#define BIT_CLEAR(a, b) ((a) &= ~(1U << (b)))

SerialStatus serialStatusFlag;
SerialStatus serialSecondaryStatusFlag;

//!@{
/** @brief Hard coded response for some TS messages.
 * @attention Stored in flash (.text segment) and loaded on demand.
 */
constexpr byte serialVersion[] PROGMEM = {SERIAL_RC_OK, '0', '0', '2'};
constexpr byte canId[] PROGMEM = {SERIAL_RC_OK, 0};
constexpr byte codeVersion[] = {SERIAL_RC_OK, 'A', 'D', 'V', 'd', 'a', 's', 'h', ' ', '2', '0', '2', '4', 'd', 'e', 'v'}; // Note no null terminator in array and statu variable at the start
constexpr byte productString[] PROGMEM = {SERIAL_RC_OK, 'A', 'D', 'V', 'd', 'a', 's', 'h', ' ', '2', '0', '2', '4', 'd', 'e', 'v'};
// constexpr byte codeVersion[] PROGMEM = { SERIAL_RC_OK, 's','p','e','e','d','u','i','n','o',' ','2','0','2','4','0','2'} ; //Note no null terminator in array and statu variable at the start
// constexpr byte productString[] PROGMEM = { SERIAL_RC_OK, 'S', 'p', 'e', 'e', 'd', 'u', 'i', 'n', 'o', ' ', '2', '0', '2', '4', '.', '0', '2'};
constexpr byte testCommsResponse[] PROGMEM = {SERIAL_RC_OK, 255};
//!@}

/** @brief The number of bytes received or transmitted to date during nonblocking I/O.
 *
 * @attention We can share one variable between rx & tx because we only support simpex serial comms.
 * I.e. we can only be receiving or transmitting at any one time.
 */
static uint16_t serialBytesRxTx = 0;
static uint32_t serialReceiveStartTime = 0; //!< The time at which the serial receive started. Used for calculating whether a timeout has occurred */
static FastCRC32 CRC32_serial;              //!< Support accumulation of a CRC during non-blocking operations */
using crc_t = uint32_t;

static uint8_t serialPayload[SERIAL_BUFFER_SIZE]; //!< Serial payload buffer. */
static uint16_t serialPayloadLength = 0;          //!< How many bytes in serialPayload were received or sent */

static inline bool isTimeout(void)
{
  return (millis() - serialReceiveStartTime) > SERIAL_TIMEOUT;
}

// ====================================== Endianness Support =============================

/**
 * @brief      Flush all remaining bytes from the rx serial buffer
 */
void flushRXbuffer(void)
{
  while (Serial.available() > 0)
  {
    Serial.read();
  }
}

/** @brief Reverse the byte order of a uint32_t
 *
 * @attention noinline is needed to prevent enlarging callers stack frame, which in turn throws
 * off free ram reporting.
 * */
static __attribute__((noinline)) uint32_t reverse_bytes(uint32_t i)
{
  return ((i >> 24) & 0xffU) |    // move byte 3 to byte 0
         ((i << 8) & 0xff0000U) | // move byte 1 to byte 2
         ((i >> 8) & 0xff00U) |   // move byte 2 to byte 1
         ((i << 24) & 0xff000000U);
}

// ====================================== Blocking IO Support ================================

void writeByteReliableBlocking(byte value)
{
  // Some platforms (I'm looking at you Teensy 3.5) do not mimic the Arduino 1.0
  // contract and synchronously block.
  // https://github.com/PaulStoffregen/cores/blob/master/teensy3/usb_serial.c#L215
  while (!Serial.availableForWrite())
  { /* Wait for the buffer to free up space */
  }
  Serial.write(value);
}

// ====================================== Multibyte Primitive IO Support =============================

/** @brief Read a uint32_t from Serial
 *
 * @attention noinline is needed to prevent enlarging callers stack frame, which in turn throws
 * off free ram reporting.
 * */
static __attribute__((noinline)) uint32_t readSerial32Timeout(void)
{
  union
  {
    char raw[sizeof(uint32_t)];
    uint32_t value;
  } buffer;
  // Teensy 3.5: Serial.available() should only be used as a boolean test
  // See https://www.pjrc.com/teensy/td_serial.html#singlebytepackets
  size_t count = 0;
  while (count < sizeof(buffer.value))
  {
    if (Serial.available() != 0)
    {
      buffer.raw[count++] = (byte)Serial.read();
    }
    else if (isTimeout())
    {
      return 0;
    }
    else
    { /* MISRA - no-op */
    }
  }
  return reverse_bytes(buffer.value);
}

/** @brief Write a uint32_t to Serial
 * @returns The value as transmitted on the wire
 */
static uint32_t serialWrite(uint32_t value)
{
  value = reverse_bytes(value);
  const byte *pBuffer = (const byte *)&value;
  writeByteReliableBlocking(pBuffer[0]);
  writeByteReliableBlocking(pBuffer[1]);
  writeByteReliableBlocking(pBuffer[2]);
  writeByteReliableBlocking(pBuffer[3]);
  return value;
}

/** @brief Write a uint16_t to Serial */
static void serialWrite(uint16_t value)
{
  writeByteReliableBlocking((value >> 8U) & 255U);
  writeByteReliableBlocking(value & 255U);
}

// ====================================== Non-blocking IO Support =============================

/** @brief Send as much data as possible without blocking the caller
 * @return Number of bytes sent
 */
static uint16_t writeNonBlocking(const byte *buffer, size_t length)
{
  uint16_t bytesTransmitted = 0;

  while (bytesTransmitted < length && Serial.availableForWrite() != 0
         // Just in case
         && Serial.write(buffer[bytesTransmitted]) == 1)
  {
    bytesTransmitted++;
  }

  return bytesTransmitted;

  // This doesn't work on Teensy.
  // See https://github.com/PaulStoffregen/cores/issues/10#issuecomment-61514955
  // size_t capacity = min((size_t)Serial.availableForWrite(), length);
  // return Serial.write(buffer, capacity);
}

/** @brief Write a uint32_t to Serial without blocking the caller
 * @return Number of bytes sent
 */
static size_t writeNonBlocking(size_t start, uint32_t value)
{
  value = reverse_bytes(value);
  const byte *pBuffer = (const byte *)&value;
  return writeNonBlocking(pBuffer + start, sizeof(value) - start); // cppcheck-suppress misra-c2012-17.2
}

/** @brief Send the buffer, followed by it's CRC
 *
 * This is supposed to be called multiple times for the same buffer until
 * it's all sent.
 *
 * @param start Index into the buffer to start sending at. [0, length)
 * @param length Total size of the buffer
 * @return Cumulative total number of bytes written . I.e. the next start value
 */
static uint16_t sendBufferAndCrcNonBlocking(const byte *buffer, size_t start, size_t length)
{
  if (start < length)
  {
    start = start + writeNonBlocking(buffer + start, length - start);
  }

  if (start >= length && start < length + sizeof(crc_t))
  {
    start = start + writeNonBlocking(start - length, CRC32_serial.crc32(buffer, length));
  }

  return start;
}

/** @brief Start sending the shared serialPayload buffer.
 *
 * ::serialStatusFlag will be signal the result of the send:<br>
 * ::serialStatusFlag == SERIAL_INACTIVE: send is complete <br>
 * ::serialStatusFlag == SERIAL_TRANSMIT_INPROGRESS: partial send, subsequent calls to continueSerialTransmission
 * will finish sending serialPayload
 *
 * @param payloadLength How many bytes to send [0, sizeof(serialPayload))
 */
static void sendSerialPayloadNonBlocking(uint16_t payloadLength)
{
  // Start new transmission session
  serialStatusFlag = SERIAL_TRANSMIT_INPROGRESS;
  serialWrite(payloadLength);
  serialPayloadLength = payloadLength;
  serialBytesRxTx = sendBufferAndCrcNonBlocking(serialPayload, 0, payloadLength);
  serialStatusFlag = serialBytesRxTx == payloadLength + sizeof(crc_t) ? SERIAL_INACTIVE : SERIAL_TRANSMIT_INPROGRESS;
}

// ====================================== TS Message Support =============================

/** @brief Send a message to TS containing only a return code.
 *
 * This is used when TS asks for an action to happen (E.g. start a logger) or
 * to signal an error condition to TS
 *
 * @attention This is a blocking operation
 */
static void sendReturnCodeMsg(byte returnCode)
{
  serialWrite((uint16_t)sizeof(returnCode));
  writeByteReliableBlocking(returnCode);
  serialWrite(CRC32_serial.crc32(&returnCode, sizeof(returnCode)));
}

// ====================================== Command/Action Support =============================

// The functions in this section are abstracted out to prevent enlarging callers stack frame,
// which in turn throws off free ram reporting.

/**
 * @brief Update a pages contents from a buffer
 *
 * @param pageNum The index of the page to update
 * @param offset Offset into the page
 * @param buffer The buffer to read from
 * @param length The buffer length
 * @return true if page updated successfully
 * @return false if page cannot be updated
 */
static bool updatePageValues(uint8_t pageNum, uint16_t offset, const byte *buffer, uint16_t length)
{
  if ((offset + length) <= getPageSize(pageNum))
  {
    for (uint16_t i = 0; i < length; i++)
    {
      // setPageValue(pageNum, (offset + i), buffer[i]);
    }
    // deferEEPROMWritesUntil = micros() + EEPROM_DEFER_DELAY;
    return true;
  }

  return false;
}

/**
 * @brief Loads a pages contents into a buffer
 *
 * @param pageNum The index of the page to update
 * @param offset Offset into the page
 * @param buffer The buffer to read from
 * @param length The buffer length
 */
static void loadPageValuesToBuffer(uint8_t pageNum, uint16_t offset, byte *buffer, uint16_t length)
{
  for (uint16_t i = 0; i < length; i++)
  {
    // buffer[i] = getPageValue(pageNum, offset + i);
  }
}

/** @brief Send a status record back to tuning/logging SW.
 * This will "live" information from @ref currentStatus struct.
 * @param offset - Start field number
 * @param packetLength - Length of actual message (after possible ack/confirm headers)
 * E.g. tuning sw command 'A' (Send all values) will send data from field number 0, LOG_ENTRY_SIZE fields.
 */
static void generateLiveValues(uint16_t offset, uint16_t packetLength)
{
  if (firstCommsRequest)
  {
    firstCommsRequest = false;
    secl = 0;
  }

  // currentStatus.spark ^= (-currentStatus.hasSync ^ currentStatus.spark) & (1U << BIT_SPARK_SYNC); //Set the sync bit of the Spark variable to match the hasSync variable

  serialPayload[0] = SERIAL_RC_OK;
  for (byte x = 0; x < packetLength; x++)
  {
    // serialPayload[x+1] = getTSLogEntry(offset+x);
  }
  // Reset any flags that are being used to trigger page refreshes
  // BIT_CLEAR(currentStatus.status3, BIT_STATUS3_VSS_REFRESH);
}

// ====================================== End Internal Functions =============================

/** Processes the incoming data on the serial buffer based on the command sent.
Can be either data for a new command or a continuation of data for command that is already in progress:

Commands are single byte (letter symbol) commands.
*/

void serial_comms(void *pvParameters)
{
  while (1)
  {
    if (serialTransmitInProgress())
    {
      serialTransmit();
    }

    // Check for any new or in-progress requests from serial.
    if (Serial.available() > 0 || serialRecieveInProgress())
    {
      serialReceive();
    }
  }
}

void SerialCommsInit(void)
{
  xTaskCreatePinnedToCore(serial_comms, "serial comms", 10000, NULL, 0, NULL, APP_CPU_NUM);
}

void serialReceive(void)
{
  // Check for an existing legacy command in progress
  if (serialStatusFlag == SERIAL_COMMAND_INPROGRESS_LEGACY)
  {
    // legacySerialCommand();
    return;
  }

  if (Serial.available() != 0 && serialStatusFlag == SERIAL_INACTIVE)
  {
    // New command received
    // Need at least 2 bytes to read the length of the command
    byte highByte = (byte)Serial.peek();

    // Check if the command is legacy using the call/response mechanism
    if (highByte == 'F')
    {
      // F command is always allowed as it provides the initial serial protocol version.
      Serial.print(F("002"));
      return;
    }
    else
    {
      Serial.read();
      while (Serial.available() == 0)
      { /* Wait for the 2nd byte to be received (This will almost never happen) */
      }

      serialPayloadLength = word(highByte, Serial.read());
      serialBytesRxTx = 2;
      serialStatusFlag = SERIAL_RECEIVE_INPROGRESS; // Flag the serial receive as being in progress
      serialReceiveStartTime = millis();
    }
  }

  // If there is a serial receive in progress, read as much from the buffer as possible or until we receive all bytes
  while ((Serial.available() > 0) && (serialStatusFlag == SERIAL_RECEIVE_INPROGRESS))
  {
    if (serialBytesRxTx < (serialPayloadLength + SERIAL_LEN_SIZE))
    {
      serialPayload[serialBytesRxTx - SERIAL_LEN_SIZE] = (byte)Serial.read();
      serialBytesRxTx++;
    }
    else
    {
      uint32_t incomingCrc = readSerial32Timeout();
      serialStatusFlag = SERIAL_INACTIVE; // The serial receive is now complete

      if (!isTimeout()) // CRC read can timeout also!
      {
        if (incomingCrc == CRC32_serial.crc32(serialPayload, serialPayloadLength))
        {
          // CRC is correct. Process the command
          processSerialCommand();
          // BIT_CLEAR(currentStatus.status4, BIT_STATUS4_ALLOW_LEGACY_COMMS); //Lock out legacy commands until next power cycle
        }
        else
        {
          // CRC Error. Need to send an error message
          sendReturnCodeMsg(SERIAL_RC_CRC_ERR);
          flushRXbuffer();
        }
      }
      // else timeout - code below will kick in.
    }
  } // Data in serial buffer and serial receive in progress

  // Check for a timeout
  if (isTimeout())
  {
    serialStatusFlag = SERIAL_INACTIVE; // Reset the serial receive

    flushRXbuffer();
    sendReturnCodeMsg(SERIAL_RC_TIMEOUT);

  } // Timeout
}

void serialTransmit(void)
{
  switch (serialStatusFlag)
  {
  case SERIAL_TRANSMIT_INPROGRESS_LEGACY:
    // sendValues(logItemsTransmitted, inProgressLength, SEND_OUTPUT_CHANNELS, Serial, serialStatusFlag);
    break;

  case SERIAL_TRANSMIT_TOOTH_INPROGRESS:
    // sendToothLog();
    break;

  case SERIAL_TRANSMIT_TOOTH_INPROGRESS_LEGACY:
    // sendToothLog_legacy(logItemsTransmitted);
    break;

  case SERIAL_TRANSMIT_COMPOSITE_INPROGRESS:
    // sendCompositeLog();
    break;

  case SERIAL_TRANSMIT_INPROGRESS:
    serialBytesRxTx = sendBufferAndCrcNonBlocking(serialPayload, serialBytesRxTx, serialPayloadLength);
    serialStatusFlag = serialBytesRxTx == serialPayloadLength + sizeof(crc_t) ? SERIAL_INACTIVE : SERIAL_TRANSMIT_INPROGRESS;
    break;

  default: // Nothing to do
    break;
  }
}

void processSerialCommand(void)
{
  switch (serialPayload[0])
  {

  case 'A': // send x bytes of realtime values in legacy support format
    generateLiveValues(0, LOG_ENTRY_SIZE);
    break;

  case 'b': // New EEPROM burn command to only burn a single page at a time
    if ((micros() > deferEEPROMWritesUntil))
    {
      writeConfig(serialPayload[2]);
    } // Read the table number and perform burn. Note that byte 1 in the array is unused
    else
    {
    }

    sendReturnCodeMsg(SERIAL_RC_BURN_OK);
    break;

  case 'B': // Same as above, but for the comms compat mode. Slows down the burn rate and increases the defer time
    // sendReturnCodeMsg(SERIAL_RC_BURN_OK);
    break;

  case 'C': // test communications. This is used by Tunerstudio to see whether there is an ECU on a given serial port
    (void)memcpy_P(serialPayload, testCommsResponse, sizeof(testCommsResponse));
    sendSerialPayloadNonBlocking(sizeof(testCommsResponse));
    break;

  case 'd': // Send a CRC32 hash of a given page
  {
    uint32_t CRC32_val = reverse_bytes(calculatePageCRC32(serialPayload[2]));

    serialPayload[0] = SERIAL_RC_OK;
    (void)memcpy(&serialPayload[1], &CRC32_val, sizeof(CRC32_val));
    sendSerialPayloadNonBlocking(5);
    break;
  }

  case 'E': // receive command button commands
    //(void)TS_CommandButtonsHandler(word(serialPayload[1], serialPayload[2]));
    sendReturnCodeMsg(SERIAL_RC_OK);
    break;

  case 'f': // Send serial capability details
    serialPayload[0] = SERIAL_RC_OK;
    serialPayload[1] = 2; // Serial protocol version
    serialPayload[2] = highByte(BLOCKING_FACTOR);
    serialPayload[3] = lowByte(BLOCKING_FACTOR);
    serialPayload[4] = highByte(TABLE_BLOCKING_FACTOR);
    serialPayload[5] = lowByte(TABLE_BLOCKING_FACTOR);

    sendSerialPayloadNonBlocking(6);
    break;

  case 'F': // send serial protocol version
    (void)memcpy_P(serialPayload, serialVersion, sizeof(serialVersion));
    sendSerialPayloadNonBlocking(sizeof(serialVersion));
    break;

  case 'H': // Start the tooth logger
    // startToothLogger();
    // sendReturnCodeMsg(SERIAL_RC_OK);
    break;

  case 'h': // Stop the tooth logger
    // stopToothLogger();
    // sendReturnCodeMsg(SERIAL_RC_OK);
    break;

  case 'I': // send CAN ID
    (void)memcpy_P(serialPayload, canId, sizeof(canId));
    sendSerialPayloadNonBlocking(sizeof(serialVersion));
    break;

  case 'J': // Start the composite logger
    // startCompositeLogger();
    // sendReturnCodeMsg(SERIAL_RC_OK);
    break;

  case 'j': // Stop the composite logger
    // stopCompositeLogger();
    // sendReturnCodeMsg(SERIAL_RC_OK);
    break;

  case 'k': // Send CRC values for the calibration pages
  {
    uint32_t CRC32_val = reverse_bytes(readCalibrationCRC32(serialPayload[2])); // Get the CRC for the requested page

    serialPayload[0] = SERIAL_RC_OK;
    (void)memcpy(&serialPayload[1], &CRC32_val, sizeof(CRC32_val));
    sendSerialPayloadNonBlocking(5);
    break;
  }

  case 'M':
  {
    // New write command
    // 7 bytes required:
    // 2 - Page identifier
    // 2 - offset
    // 2 - Length
    // 1 - 1st New value
    if (updatePageValues(serialPayload[2], word(serialPayload[4], serialPayload[3]), &serialPayload[7], word(serialPayload[6], serialPayload[5])))
    {
      sendReturnCodeMsg(SERIAL_RC_OK);
    }
    else
    {
      // This should never happen, but just in case
      sendReturnCodeMsg(SERIAL_RC_RANGE_ERR);
    }
    break;
  }

  case 'O': // Start the composite logger 2nd cam (teritary)
    // startCompositeLoggerTertiary();
    // sendReturnCodeMsg(SERIAL_RC_OK);
    break;

  case 'o': // Stop the composite logger 2nd cam (tertiary)
    // stopCompositeLoggerTertiary();
    // sendReturnCodeMsg(SERIAL_RC_OK);
    break;

  case 'X': // Start the composite logger 2nd cam (teritary)
    // startCompositeLoggerCams();
    // sendReturnCodeMsg(SERIAL_RC_OK);
    break;

  case 'x': // Stop the composite logger 2nd cam (tertiary)
    // stopCompositeLoggerCams();
    // sendReturnCodeMsg(SERIAL_RC_OK);
    break;

  /*
   * New method for sending page values (MS command equivalent is 'r')
   */
  case 'p':
  {
    // 6 bytes required:
    // 2 - Page identifier
    // 2 - offset
    // 2 - Length
    uint16_t length = word(serialPayload[6], serialPayload[5]);

    // Setup the transmit buffer
    serialPayload[0] = SERIAL_RC_OK;
    loadPageValuesToBuffer(serialPayload[2], word(serialPayload[4], serialPayload[3]), &serialPayload[1], length);
    sendSerialPayloadNonBlocking(length + 1U);
    break;
  }

  case 'Q': // send code version
    (void)memcpy_P(serialPayload, codeVersion, sizeof(codeVersion));
    sendSerialPayloadNonBlocking(sizeof(codeVersion));
    break;

  case 'r': // New format for the optimised OutputChannels
  {
    uint8_t cmd = serialPayload[2];
    uint16_t offset = word(serialPayload[4], serialPayload[3]);
    uint16_t length = word(serialPayload[6], serialPayload[5]);

    if (cmd == SEND_OUTPUT_CHANNELS) // Send output channels command 0x30 is 48dec
    {
      generateLiveValues(offset, length);
      sendSerialPayloadNonBlocking(length + 1U);
    }
    else if (cmd == 0x0f)
    {
      // Request for signature
      (void)memcpy_P(serialPayload, codeVersion, sizeof(codeVersion));
      sendSerialPayloadNonBlocking(sizeof(codeVersion));
    }

    else
    {
      // No other r/ commands should be called
    }
    break;
  }

  case 'S': // send code version
    (void)memcpy_P(serialPayload, productString, sizeof(productString));
    sendSerialPayloadNonBlocking(sizeof(productString));
    secl = 0; // This is required in TS3 due to its stricter timings
    break;

  case 'T': // Send 256 tooth log entries to Tuner Studios tooth logger

    break;

  case 't': // receive new Calibration info. Command structure: "t", <tble_idx> <data array>.
  {

    break;
  }

  case 'U': // User wants to reset the Arduino (probably for FW update)

    break;

  case 'w':
  {

    break;
  }

  default:
    // Unknown command
    sendReturnCodeMsg(SERIAL_RC_UKWN_ERR);
    break;
  }
}
