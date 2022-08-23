/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */

#include <stdint.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s_pdm.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "sdkconfig.h"
#include "i2s_pdm_example.h"

#define EXAMPLE_PDM_RX_CLK_IO           GPIO_NUM_0      // I2S PDM RX clock io number
#define EXAMPLE_PDM_RX_DIN_IO           GPIO_NUM_2      // I2S PDM RX data in io number

#define EXAMPLE_PDM_RX_FREQ_HZ          16000           // I2S PDM RX frequency


static i2s_chan_handle_t i2s_example_init_pdm_rx(void)
{
    i2s_chan_handle_t rx_chan;        // I2S rx channel handler
    /* Setp 1: Determine the I2S channel configuration and allocate RX channel only
     * The default configuration can be generated by the helper macro,
     * but note that PDM channel can only be registered on I2S_NUM_0 */
    i2s_chan_config_t rx_chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_AUTO, I2S_ROLE_MASTER);
    ESP_ERROR_CHECK(i2s_new_channel(&rx_chan_cfg, NULL, &rx_chan));

    /* Step 2: Setting the configurations of PDM RX mode and initialize the RX channel
     * The slot configuration and clock configuration can be generated by the macros
     * These two helper macros is defined in 'i2s_pdm.h' which can only be used in PDM RX mode.
     * They can help to specify the slot and clock configurations for initialization or re-configuring */
    i2s_pdm_rx_config_t pdm_rx_cfg = {
        .clk_cfg = I2S_PDM_RX_CLK_DEFAULT_CONFIG(EXAMPLE_PDM_RX_FREQ_HZ),
        /* The data bit-width of PDM mode is fixed to 16 */
        .slot_cfg = I2S_PDM_RX_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO),
        .gpio_cfg = {
            .clk = EXAMPLE_PDM_RX_CLK_IO,
            .din = EXAMPLE_PDM_RX_DIN_IO,
            .invert_flags = {
                .clk_inv = false,
            },
        },
    };
    ESP_ERROR_CHECK(i2s_channel_init_pdm_rx_mode(rx_chan, &pdm_rx_cfg));

    /* Step 3: Enable the rx channels before reading data */
    ESP_ERROR_CHECK(i2s_channel_enable(rx_chan));
    return rx_chan;
}


void i2s_example_pdm_rx_task(void *args)
{
    int16_t *r_buf = (int16_t *)calloc(1, EXAMPLE_BUFF_SIZE);
    assert(r_buf);
    i2s_chan_handle_t rx_chan = i2s_example_init_pdm_rx();

    size_t r_bytes = 0;
    while (1) {
        /* Read i2s data */
        if (i2s_channel_read(rx_chan, r_buf, EXAMPLE_BUFF_SIZE, &r_bytes, 1000) == ESP_OK) {
            printf("Read Task: i2s read %d bytes\n-----------------------------------\n", r_bytes);
            printf("[0] %d [1] %d [2] %d [3] %d\n[4] %d [5] %d [6] %d [7] %d\n\n",
                   r_buf[0], r_buf[1], r_buf[2], r_buf[3], r_buf[4], r_buf[5], r_buf[6], r_buf[7]);
        } else {
            printf("Read Task: i2s read failed\n");
        }
        vTaskDelay(pdMS_TO_TICKS(200));
    }
    free(r_buf);
    vTaskDelete(NULL);
}
