#include <stdio.h>
#include "ecat_slv.h"
#include "utypes.h"
#include <bcm2835.h>
#include <unistd.h>
#include <stdlib.h>

/* Application variables */
_Objects Obj;
_Mbuffer Mb;

void cb_get_inputs(void)
{
    // Callback for retrieving inputs (optional)
}

void cb_set_outputs(void)
{
    // Callback for setting outputs (optional)
}

// Function to generate a random value in the range [-100, 100]
int16_t generate_random_value(void)
{
    return (int16_t)(rand() % 201 - 100);
}

int8_t received_data = 0; // Global variable to store received data

// Function to transmit data via SPI
void SPI_transmit(int16_t data)
{
    printf("Transmitting Value: %d\n", data);
    int8_t send_data = (int8_t)(data);
    int8_t received_data_unit = (int8_t)bcm2835_spi_transfer((uint8_t)send_data);
    received_data = received_data_unit;
    int16_t processed_data = (int16_t)(received_data);
    printf("Received Value: %d\n", processed_data);
}

// Callback for transmitting data
void cb_transmit(void)
{
    // Transmit random negative value via SPI
    int16_t transmit_value;
    
    do {
        transmit_value = generate_random_value();
    } while (transmit_value == 56);
    
    SPI_transmit(transmit_value);

    // Receive and interpret the received data
    int16_t received_value = (int16_t)(received_data & 0xFF); // Convert the received data to a signed value
    if (received_value > 127) {
        received_value -= 256;
    }
    Obj.in.IMU1_Pitch = (int16_t)transmit_value;
}

// Main run function
int main_run(void *arg)
{
    static esc_cfg_t config =
    {
        .user_arg = "rpi4,cs1",
        .use_interrupt = 0,
        .watchdog_cnt = 150,
        .set_defaults_hook = NULL,
        .pre_state_change_hook = NULL,
        .post_state_change_hook = NULL,
        .application_hook = NULL,
        .safeoutput_override = NULL,
        .pre_object_download_hook = NULL,
        .post_object_download_hook = NULL,
        .rxpdo_override = NULL,
        .txpdo_override = NULL,
        .esc_hw_interrupt_enable = NULL,
        .esc_hw_interrupt_disable = NULL,
        .esc_hw_eep_handler = NULL,
        .esc_check_dc_handler = NULL,
    };

    ecat_slv_init(&config);

    while (1)
    {
        ecat_slv();
        cb_transmit();
    }

    return 0;
}

int main(void)
{
    main_run(NULL);
    return 0;
}
