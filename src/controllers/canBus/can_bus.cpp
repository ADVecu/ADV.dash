#include <driver/twai.h>
#include <driver/gpio.h>
#include "rus_efi_can_verbose.h"
#include <Arduino.h>

// Can Bus Transceiver Pins
#define CAN_TX_PIN GPIO_NUM_18
#define CAN_RX_PIN GPIO_NUM_17

rus_efi_can_verbose_base0_t rus_efi_can_verbose_base0;
rus_efi_can_verbose_base1_t rus_efi_can_verbose_base1;
rus_efi_can_verbose_base2_t rus_efi_can_verbose_base2;
rus_efi_can_verbose_base3_t rus_efi_can_verbose_base3;
rus_efi_can_verbose_base4_t rus_efi_can_verbose_base4;
rus_efi_can_verbose_base5_t rus_efi_can_verbose_base5;
rus_efi_can_verbose_base6_t rus_efi_can_verbose_base6;
rus_efi_can_verbose_base7_t rus_efi_can_verbose_base7;
rus_efi_can_verbose_base8_t rus_efi_can_verbose_base8;


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

    rus_efi_can_verbose_base0_init(&rus_efi_can_verbose_base0);
    rus_efi_can_verbose_base1_init(&rus_efi_can_verbose_base1);
    rus_efi_can_verbose_base2_init(&rus_efi_can_verbose_base2);
    rus_efi_can_verbose_base3_init(&rus_efi_can_verbose_base3);
    rus_efi_can_verbose_base4_init(&rus_efi_can_verbose_base4);
    rus_efi_can_verbose_base5_init(&rus_efi_can_verbose_base5);
    rus_efi_can_verbose_base6_init(&rus_efi_can_verbose_base6);
    rus_efi_can_verbose_base7_init(&rus_efi_can_verbose_base7);
    rus_efi_can_verbose_base8_init(&rus_efi_can_verbose_base8);

}

//read the CAN bus for messages
void canbus_read()
{
    twai_message_t rx_msg;
    if (twai_receive(&rx_msg, pdMS_TO_TICKS(1000)) == ESP_OK)
    {
        switch (rx_msg.identifier)
        {
            case RUS_EFI_CAN_VERBOSE_BASE0_FRAME_ID:
                rus_efi_can_verbose_base0_unpack(&rus_efi_can_verbose_base0, rx_msg.data, rx_msg.data_length_code);
                break;
            case RUS_EFI_CAN_VERBOSE_BASE1_FRAME_ID:
                rus_efi_can_verbose_base1_unpack(&rus_efi_can_verbose_base1, rx_msg.data, rx_msg.data_length_code);
                break;
        }

        Serial.print(rus_efi_can_verbose_base1.rpm);

    }
    else
    {
        printf("Failed to receive message\n");
    }
}