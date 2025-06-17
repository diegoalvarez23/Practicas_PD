#include "INMP441.h"
#include <driver/i2s.h>
#include <string.h>  // Per memset

void INMP441::begin() {
    const i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
        .sample_rate = 16000,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,  // ✅ Format recomanat
        .intr_alloc_flags = 0,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .use_apll = false,
        .tx_desc_auto_clear = false,
        .fixed_mclk = 0
    };

    const i2s_pin_config_t pin_config = {
        .bck_io_num = GPIO_NUM_15,
        .ws_io_num = GPIO_NUM_16,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = GPIO_NUM_17
    };

    i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM_0, &pin_config);
}

void INMP441::read(int16_t* buffer, size_t len) {
    size_t total_bytes_read = 0;
    memset(buffer, 0, len * sizeof(int16_t));  // 🧹 Neteja el buffer abans d'usar-lo

    while (total_bytes_read < len * sizeof(int16_t)) {
        size_t bytes_read = 0;
        i2s_read(I2S_NUM_0,
                 ((uint8_t*)buffer) + total_bytes_read,
                 (len * sizeof(int16_t)) - total_bytes_read,
                 &bytes_read, 100);
        if (bytes_read == 0) break;  // Timeout o error
        total_bytes_read += bytes_read;
    }

    // 🔊 Amplificació del senyal (opcional)
    for (size_t i = 0; i < len; i++) {
        buffer[i] = buffer[i] * 4;
    }
}
