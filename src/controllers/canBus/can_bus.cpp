/*
    Console Prompt to generate the CAN Messages C++ code:
    python -m cantools generate_c_source --no-floating-point-numbers --database-name rus_efi_can_verbose rusEFI+PRO_CAN.dbc
*/

#include <driver/twai.h>
#include <driver/gpio.h>
#include "rus_efi_can_verbose.h"
#include "can_bus.h"
#include "pcb_definitions.h"
#include <muTimer.h>

canbus_encode_msg canbus_encode;
muTimer canbusDataRate;

#define CANBUS_DEBUG 0 // Set to 1 to print CAN messages and debug info

void canbus_init()
{
    // CAN BUS Init
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(CAN_TX_PIN, CAN_RX_PIN, TWAI_MODE_NORMAL);
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    // Install TWAI driver
    // gpio_reset_pin(CAN_TX_PIN);
    // gpio_reset_pin(CAN_RX_PIN);
    if (twai_driver_install(&g_config, &t_config, &f_config) == ESP_OK)
    {
        printf("Driver installed\n");
    }
    else
    {
        printf("Failed to install driver\n");
        return;
    }

    // Start TWAI driver
    if (twai_start() == ESP_OK)
    {
        printf("Driver started\n");
    }
    else
    {
        printf("Failed to start driver\n");
        return;
    }

    canbus_encode.levels_duty = 0.5;
    canbus_encode.battery_voltage = 0.001;
    canbus_encode.temps = 40;
    canbus_encode.pressures = 0.033;
    canbus_encode.ign_advance = 0.2;
    canbus_encode.pwm = 0.0033;
    canbus_encode.lambda = 0.0001;
    canbus_encode.afr = 14.7;
    canbus_encode.tps = 0.01;

    // Create a queue to handle CAN messages traduced by the canbus_read task

    // Task to read the CAN bus
    xTaskCreatePinnedToCore(canbus_read, "canbus_read", 10000, NULL, 1, NULL, APP_CPU_NUM);

}

// read the CAN bus for messages
void canbus_read(void *pvParameters)
{

    // Initialize RUS EFI CAN Messages Structs
    rus_efi_can_verbose_base0_t rus_efi_can_verbose_base0;
    rus_efi_can_verbose_base1_t rus_efi_can_verbose_base1;
    rus_efi_can_verbose_base2_t rus_efi_can_verbose_base2;
    rus_efi_can_verbose_base3_t rus_efi_can_verbose_base3;
    rus_efi_can_verbose_base4_t rus_efi_can_verbose_base4;
    rus_efi_can_verbose_base5_t rus_efi_can_verbose_base5;
    rus_efi_can_verbose_base6_t rus_efi_can_verbose_base6;
    rus_efi_can_verbose_base7_t rus_efi_can_verbose_base7;
    rus_efi_can_verbose_base8_t rus_efi_can_verbose_base8;
    rus_efi_can_verbose_pro0_t rus_efi_can_verbose_pro0;
    rus_efi_can_verbose_pro1_t rus_efi_can_verbose_pro1;
    rus_efi_can_verbose_pro3_t rus_efi_can_verbose_pro3;
    rus_efi_can_verbose_pro5_t rus_efi_can_verbose_pro5;
    rus_efi_can_verbose_pro6_t rus_efi_can_verbose_pro6;

    // Set the default values for the structs
    rus_efi_can_verbose_base0_init(&rus_efi_can_verbose_base0);
    rus_efi_can_verbose_base1_init(&rus_efi_can_verbose_base1);
    rus_efi_can_verbose_base2_init(&rus_efi_can_verbose_base2);
    rus_efi_can_verbose_base3_init(&rus_efi_can_verbose_base3);
    rus_efi_can_verbose_base4_init(&rus_efi_can_verbose_base4);
    rus_efi_can_verbose_base5_init(&rus_efi_can_verbose_base5);
    rus_efi_can_verbose_base6_init(&rus_efi_can_verbose_base6);
    rus_efi_can_verbose_base7_init(&rus_efi_can_verbose_base7);
    rus_efi_can_verbose_base8_init(&rus_efi_can_verbose_base8);
    rus_efi_can_verbose_pro0_init(&rus_efi_can_verbose_pro0);
    rus_efi_can_verbose_pro1_init(&rus_efi_can_verbose_pro1);
    rus_efi_can_verbose_pro3_init(&rus_efi_can_verbose_pro3);
    rus_efi_can_verbose_pro5_init(&rus_efi_can_verbose_pro5);
    rus_efi_can_verbose_pro6_init(&rus_efi_can_verbose_pro6);

    // Initialize the CAN message struct
    twai_message_t rx_msg;

    // Create a queue to handle CAN messages traduced by the canbus_read task
    canbus_queue = xQueueCreate(10, sizeof(canbus_data_t));

    while (1)
    {

        // Receive a CAN message
        // capture error and print it
        int err = twai_receive(&rx_msg, pdMS_TO_TICKS(1000));

        if (err == ESP_OK)
        {
#if CANBUS_DEBUG

            // PRINT CAN MESSAGE
            printf("CAN Message Received\n");
            printf("ID: %d\n", rx_msg.identifier);
            printf("Data: ");
            for (int i = 0; i < rx_msg.data_length_code; i++)
            {
                printf("%d ", rx_msg.data[i]);
            }
            printf("\n");

#endif

            // Parce the received CAN message into the correct struct
            switch (rx_msg.identifier)
            {
            case RUS_EFI_CAN_VERBOSE_BASE0_FRAME_ID:
                rus_efi_can_verbose_base0_unpack(&rus_efi_can_verbose_base0, rx_msg.data, rx_msg.data_length_code);
                break;
            case RUS_EFI_CAN_VERBOSE_BASE1_FRAME_ID:
                rus_efi_can_verbose_base1_unpack(&rus_efi_can_verbose_base1, rx_msg.data, rx_msg.data_length_code);
                break;
            case RUS_EFI_CAN_VERBOSE_BASE2_FRAME_ID:
                rus_efi_can_verbose_base2_unpack(&rus_efi_can_verbose_base2, rx_msg.data, rx_msg.data_length_code);
                break;
            case RUS_EFI_CAN_VERBOSE_BASE3_FRAME_ID:
                rus_efi_can_verbose_base3_unpack(&rus_efi_can_verbose_base3, rx_msg.data, rx_msg.data_length_code);
                break;
            case RUS_EFI_CAN_VERBOSE_BASE4_FRAME_ID:
                rus_efi_can_verbose_base4_unpack(&rus_efi_can_verbose_base4, rx_msg.data, rx_msg.data_length_code);
                break;
            case RUS_EFI_CAN_VERBOSE_BASE5_FRAME_ID:
                rus_efi_can_verbose_base5_unpack(&rus_efi_can_verbose_base5, rx_msg.data, rx_msg.data_length_code);
                break;
            case RUS_EFI_CAN_VERBOSE_BASE6_FRAME_ID:
                rus_efi_can_verbose_base6_unpack(&rus_efi_can_verbose_base6, rx_msg.data, rx_msg.data_length_code);
                break;
            case RUS_EFI_CAN_VERBOSE_BASE7_FRAME_ID:
                rus_efi_can_verbose_base7_unpack(&rus_efi_can_verbose_base7, rx_msg.data, rx_msg.data_length_code);
                break;
            case RUS_EFI_CAN_VERBOSE_BASE8_FRAME_ID:
                rus_efi_can_verbose_base8_unpack(&rus_efi_can_verbose_base8, rx_msg.data, rx_msg.data_length_code);
                break;
            case RUS_EFI_CAN_VERBOSE_PRO0_FRAME_ID:
                rus_efi_can_verbose_pro0_unpack(&rus_efi_can_verbose_pro0, rx_msg.data, rx_msg.data_length_code);
                break;
            case RUS_EFI_CAN_VERBOSE_PRO1_FRAME_ID:
                rus_efi_can_verbose_pro1_unpack(&rus_efi_can_verbose_pro1, rx_msg.data, rx_msg.data_length_code);
                break;
            case RUS_EFI_CAN_VERBOSE_PRO3_FRAME_ID:
                rus_efi_can_verbose_pro3_unpack(&rus_efi_can_verbose_pro3, rx_msg.data, rx_msg.data_length_code);
                break;
            case RUS_EFI_CAN_VERBOSE_PRO5_FRAME_ID:
                rus_efi_can_verbose_pro5_unpack(&rus_efi_can_verbose_pro5, rx_msg.data, rx_msg.data_length_code);
                break;
            case RUS_EFI_CAN_VERBOSE_PRO6_FRAME_ID:
                rus_efi_can_verbose_pro6_unpack(&rus_efi_can_verbose_pro6, rx_msg.data, rx_msg.data_length_code);
                break;
            }
        }
        else
        {
            // TODO:  Handle this error, for example, send a message to the UI to display an error message on the screen, and set all the values to 0
            printf("Failed to receive message\n");
            switch (err)
            {
            case ESP_ERR_TIMEOUT:
                printf("Error: Timeout\n");
                break;
            case ESP_ERR_INVALID_ARG:
                printf("Error: Invalid Argument\n");
                break;
            case ESP_FAIL:
                printf("Error: Fail\n");
                break;
            case ESP_ERR_INVALID_STATE:
                printf("Error: Invalid State\n");
                break;
            }
        }

        // Parce the received can data into a struct for use in the UI
        canbus_data_t canbus_data;

        canbus_data.warning_counter = rus_efi_can_verbose_base0.warning_counter;
        canbus_data.last_error = rus_efi_can_verbose_base0.last_error;
        canbus_data.check_engine_act = rus_efi_can_verbose_base0.cel_act;
        canbus_data.current_gear = rus_efi_can_verbose_base0.current_gear;
        //canbus_data.current_gear = rus_efi_can_verbose_pro0.gear_sen;
        canbus_data.rpms = rus_efi_can_verbose_base1.rpm;
        canbus_data.ignition_timing = rus_efi_can_verbose_base1.ignition_timing;
        canbus_data.inj_duty = rus_efi_can_verbose_base1.inj_duty;
        canbus_data.speed = rus_efi_can_verbose_base1.vehicle_speed;
        canbus_data.tps = rus_efi_can_verbose_base2.tps1;
        canbus_data.map = rus_efi_can_verbose_base3.map;
        canbus_data.coolant_temp = (rus_efi_can_verbose_base3_coolant_temp_is_in_range(rus_efi_can_verbose_base3.coolant_temp)) ? rus_efi_can_verbose_base3.coolant_temp : -40;
        canbus_data.air_temp = (rus_efi_can_verbose_base3_intake_temp_is_in_range(rus_efi_can_verbose_base3.intake_temp)) ? rus_efi_can_verbose_base3.intake_temp : -40;
        canbus_data.aux1_temp = (rus_efi_can_verbose_base3_aux1_temp_is_in_range(rus_efi_can_verbose_base3.aux1_temp)) ? rus_efi_can_verbose_base3.aux1_temp : -40;
        canbus_data.aux2_temp = rus_efi_can_verbose_base3.aux2_temp;
        canbus_data.oil_pressure = rus_efi_can_verbose_base4.oil_press;
        canbus_data.battery_voltage = rus_efi_can_verbose_base4.batt_volt;
        canbus_data.fuel_level = rus_efi_can_verbose_base3.fuel_level;
        canbus_data.inj_pwm = rus_efi_can_verbose_base5.inj_pw;
        canbus_data.ing_duty = rus_efi_can_verbose_base1.ign_duty;
        canbus_data.mcu_temp = rus_efi_can_verbose_base3.mcu_temp;
        canbus_data.fuel_pressure = rus_efi_can_verbose_base7.fp_low;
        canbus_data.o2_sensor = rus_efi_can_verbose_base7.lam1;
        canbus_data.oil_temp = (rus_efi_can_verbose_base4_oil_temperature_is_in_range(rus_efi_can_verbose_base4.oil_temperature)) ? rus_efi_can_verbose_base4.oil_temperature : -40;

        canbus_data.fwPressure = (rus_efi_can_verbose_pro1.fw_pressure * 0.01);
        canbus_data.fwTemp = (rus_efi_can_verbose_pro1.fw_temp - 30);
        canbus_data.fwBatteryVoltage = (rus_efi_can_verbose_pro1.fw_batt_v * 0.1);
        canbus_data.rwPressure = (rus_efi_can_verbose_pro1.rw_pressure * 0.01);
        canbus_data.rwTemp = (rus_efi_can_verbose_pro1.rw_temp - 30);
        canbus_data.rwBatteryVoltage = (rus_efi_can_verbose_pro1.rw_batt_v * 0.1);
        canbus_data.ambientTemp = rus_efi_can_verbose_pro5.ambient_temp;

        canbus_data.enterBT = rus_efi_can_verbose_pro3.enter;
        canbus_data.backBT = rus_efi_can_verbose_pro3.back;
        canbus_data.upBT = rus_efi_can_verbose_pro3.up;
        canbus_data.downBT = rus_efi_can_verbose_pro3.down;
        canbus_data.aux1BT = rus_efi_can_verbose_pro3.aux1;
        canbus_data.aux2BT = rus_efi_can_verbose_pro3.aux2;
        canbus_data.aux3BT = rus_efi_can_verbose_pro3.aux3;

        canbus_data.dir_izq = rus_efi_can_verbose_pro6.dir_izq;
        canbus_data.dir_der = rus_efi_can_verbose_pro6.dir_der;
        canbus_data.high_bean = rus_efi_can_verbose_pro6.high_bean;
        canbus_data.low_bean = rus_efi_can_verbose_pro6.low_bean;
        canbus_data.fog_light = rus_efi_can_verbose_pro6.fog_light;
        canbus_data.coolant_level = rus_efi_can_verbose_pro6.coolant_level;

        uint8_t QueueError;

        // Send the CAN data to the queue for use in the UI
        QueueError = xQueueSend(canbus_queue, &canbus_data, 0);

#if CANBUS_DEBUG
        Serial.println(QueueError);
#endif
    }
}

void send_keep_alive_frame()
{
       twai_message_t tx_msg;
         tx_msg.identifier = 0x212;
            tx_msg.data_length_code = 8;
            tx_msg.data[0] = 0x00;
            tx_msg.data[1] = 0x00;
            tx_msg.data[2] = 0x00;
            tx_msg.data[3] = 0x00;
            tx_msg.data[4] = 0x00;
            tx_msg.data[5] = 0x00;
            tx_msg.data[6] = 0x00;
            tx_msg.data[7] = 0x00;
            twai_transmit(&tx_msg, pdMS_TO_TICKS(1000));
}