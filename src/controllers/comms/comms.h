/** \file comms.h
 * @brief File for handling all serial requests
 * @author Josh Stewart
 *
 * This file contains all the functions associated with serial comms.
 * This includes sending of live data, sending/receiving current page data, sending CRC values of pages, receiving sensor calibration data etc
 *
 */

#ifndef NEW_COMMS_H
#define NEW_COMMS_H

#if defined(CORE_TEENSY)
#define BLOCKING_FACTOR 251
#define TABLE_BLOCKING_FACTOR 256
#elif defined(CORE_STM32)
#define BLOCKING_FACTOR 121
#define TABLE_BLOCKING_FACTOR 64
#elif defined(CORE_AVR)
#define BLOCKING_FACTOR 121
#define TABLE_BLOCKING_FACTOR 64
#endif

enum SerialStatus
{
  /** No serial comms is in progress */
  SERIAL_INACTIVE,
  /** A partial write is in progress. */
  SERIAL_TRANSMIT_INPROGRESS,
  /** A partial write is in progress (legacy send). */
  SERIAL_TRANSMIT_INPROGRESS_LEGACY,
  /** We are part way through transmitting the tooth log */
  SERIAL_TRANSMIT_TOOTH_INPROGRESS,
  /** We are part way through transmitting the tooth log (legacy send) */
  SERIAL_TRANSMIT_TOOTH_INPROGRESS_LEGACY,
  /** We are part way through transmitting the composite log */
  SERIAL_TRANSMIT_COMPOSITE_INPROGRESS,
  /** We are part way through transmitting the composite log (legacy send) */
  SERIAL_TRANSMIT_COMPOSITE_INPROGRESS_LEGACY,
  /** Whether or not a serial request has only been partially received.
   * This occurs when a the length has been received in the serial buffer,
   * but not all of the payload or CRC has yet been received.
   *
   * Expectation is that ::serialReceive is called  until the status reverts
   * to SERIAL_INACTIVE
   */
  SERIAL_RECEIVE_INPROGRESS,
  /** We are part way through processing a legacy serial commang: call ::serialReceive */
  SERIAL_COMMAND_INPROGRESS_LEGACY,
};

/** @brief Current status of serial comms. */
extern SerialStatus serialStatusFlag;
extern SerialStatus serialSecondaryStatusFlag;

void SerialCommsInit(void);

/**
 * @brief Is a serial write in progress?
 *
 * Expectation is that ::serialTransmit is called until this
 * returns false
 */
inline bool serialTransmitInProgress(void)
{
  return serialStatusFlag == SERIAL_TRANSMIT_INPROGRESS || serialStatusFlag == SERIAL_TRANSMIT_INPROGRESS_LEGACY || serialStatusFlag == SERIAL_TRANSMIT_TOOTH_INPROGRESS || serialStatusFlag == SERIAL_TRANSMIT_TOOTH_INPROGRESS_LEGACY || serialStatusFlag == SERIAL_TRANSMIT_COMPOSITE_INPROGRESS || serialStatusFlag == SERIAL_TRANSMIT_COMPOSITE_INPROGRESS_LEGACY;
}

/**
 * @brief Is a non-blocking serial receive operation in progress?
 *
 * Expectation is the ::serialReceive is called until this
 * returns false.
 */
inline bool serialRecieveInProgress(void)
{
  return serialStatusFlag == SERIAL_RECEIVE_INPROGRESS || serialStatusFlag == SERIAL_COMMAND_INPROGRESS_LEGACY;
}

/**
 * @brief The serial receive pump. Should be called whenever the serial port
 * has data available to read.
 */
void serialReceive(void);

/** @brief The serial transmit pump. Should be called when ::serialStatusFlag indicates a transmit
 * operation is in progress */
void serialTransmit(void);

#endif // COMMS_H
