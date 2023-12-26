#include <driver/twai.h>
#include <driver/gpio.h>
#include "rus_efi_can_verbose.h"
#include "can_bus.h"

// Can Bus Transceiver Pins
#define CAN_TX_PIN GPIO_NUM_13
#define CAN_RX_PIN GPIO_NUM_12

void canbus_init()
{
    // CAN BUS Init
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(CAN_TX_PIN, CAN_RX_PIN, TWAI_MODE_NORMAL);
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    // Install TWAI driver
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

    // Initialize the CAN message struct
    twai_message_t rx_msg;

    // Create a queue to handle CAN messages traduced by the canbus_read task
    canbus_queue = xQueueCreate(10, sizeof(canbus_data_t));

    while (1)
    {
        // Receive a CAN message
        if (twai_receive(&rx_msg, pdMS_TO_TICKS(1000)) == ESP_OK)
        {
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
            }
        }
        else
        {
            // TODO:  Handle this error, for example, send a message to the UI to display an error message on the screen, and set all the values to 0
            printf("Failed to receive message\n");
        }

        // Parce the received can data into a struct for use in the UI
        canbus_data_t canbus_data;

        canbus_data.warning_counter = rus_efi_can_verbose_base0.warning_counter;
        canbus_data.last_error = rus_efi_can_verbose_base0.last_error;
        canbus_data.main_relay_act = rus_efi_can_verbose_base0.main_relay_act;
        canbus_data.fuel_pump_act = rus_efi_can_verbose_base0.fuel_pump_act;
        canbus_data.check_engine_act = rus_efi_can_verbose_base0.cel_act;
        canbus_data.current_gear = rus_efi_can_verbose_base0.current_gear;
        canbus_data.rpms = rus_efi_can_verbose_base1.rpm;
        canbus_data.ignition_timing = rus_efi_can_verbose_base1.ignition_timing;
        canbus_data.inj_duty = rus_efi_can_verbose_base1.inj_duty;
        canbus_data.speed = rus_efi_can_verbose_base1.vehicle_speed;
        canbus_data.tps = rus_efi_can_verbose_base2.tps1;
        canbus_data.map = rus_efi_can_verbose_base3.map;
        canbus_data.coolant_temp = rus_efi_can_verbose_base3.coolant_temp;
        canbus_data.air_temp = rus_efi_can_verbose_base3.intake_temp;
        canbus_data.aux1_temp = rus_efi_can_verbose_base3.aux1_temp;
        canbus_data.aux2_temp = rus_efi_can_verbose_base3.aux2_temp;
        canbus_data.oil_pressure = rus_efi_can_verbose_base4.oil_press;
        canbus_data.battery_voltage = rus_efi_can_verbose_base4.batt_volt;
        canbus_data.fuel_level = rus_efi_can_verbose_base3.fuel_level;
        canbus_data.inj_pwm = rus_efi_can_verbose_base5.inj_pw;
        canbus_data.fuel_used = rus_efi_can_verbose_base6.fuel_used;
        canbus_data.fuel_flow = rus_efi_can_verbose_base6.fuel_flow;
        canbus_data.fuel_trim = rus_efi_can_verbose_base6.fuel_trim1;
        canbus_data.fuel_pressure = rus_efi_can_verbose_base7.fp_low;
        canbus_data.o2_sensor = rus_efi_can_verbose_base7.lam1;

        // Send the CAN data to the queue for use in the UI
        xQueueSend(canbus_queue, &canbus_data, 1000);

        // vTaskDelay(10);
    }
}