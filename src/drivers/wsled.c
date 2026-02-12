
#include "esp_ws28xx.h"

uint16_t* dmaBuffer;
CRGB* wsledPixels;
static int ledCount, resetDelay, dmaBufferSize;
WsledType type;

static spi_settings_t spiSettings = {
    .host = SPI2_HOST,
    .dma_chan = SPI_DMA_CH_AUTO,
    .buscfg =
        {
            .miso_io_num = -1,
            .sclk_io_num = -1,
            .quadwp_io_num = -1,
            .quadhd_io_num = -1,
        },
    .devcfg =
        {
            .clock_speed_hz = 3.2 * 1000 * 1000, // Clock out at 3.2 MHz
            .mode = 0,                           // SPI mode 0
            .spics_io_num = -1,                  // CS pin
            .queue_size = 1,
            .command_bits = 0,
            .address_bits = 0,
            .flags = SPI_DEVICE_TXBIT_LSBFIRST,
        },
};

static const uint16_t timing_bits[16] = {
    0x1111, 0x7111, 0x1711, 0x7711, 0x1171, 0x7171, 0x1771, 0x7771,
    0x1117, 0x7117, 0x1717, 0x7717, 0x1177, 0x7177, 0x1777, 0x7777};

esp_err_t wsledInit(wsled_t* dev, CRGB** buffer) {

    type = dev->type;
    ledCount = dev->numLeds;
    resetDelay = (dev.wsledType == WS2812B) ? WSLED_12_RESET_TIME : WSLED_15_RESET_TIME;

    // 12 bytes for each led + bytes for initial zero and reset state
    dmaBufferSize = dev->numLeds * 12 + (resetDelay + 1) * 2;
    wsledPixels = malloc(sizeof(CRGB) * dev->numLeds);
    if (wsledPixels == NULL) {
        return ESP_ERR_NO_MEM;
    }
    *buffer = wsledPixels;
    spi_settings.buscfg.mosi_io_num = pin;
    spi_settings.buscfg.max_transfer_sz = dmaBufferSize;

    if (ESP_OK != spi_bus_initialize(spi_settings.host, &spi_settings.buscfg, spi_settings.dma_chan)) {
        free(wsledPixels);
        return -1;
    }

    if (ESP_OK != spi_bus_add_device(spi_settings.host, &spi_settings.devcfg, &spi_settings.spi)) {
        free(wsledPixels);
        return -1;
    }

    if (NULL == heap_caps_malloc(dmaBufferSize, MALLOC_CAP_DMA)) {
        free(wsledPixels);
        return -1;
    }
    return ESP_OK;
}

void wsledFill(CRGB color) {
    for (int i = 0; i < n_of_leds; i++) {
        ws28xx_pixels[i] = color;
    }
}

esp_err_t wsledUpdate() {

    uint32_t n = 0;

    memset(dmaBuffer, 0, dmaBufferSize);
    dmaBuffer[n++] = 0;

    for (int i = 0; i < ledCount; i++) {

        // Data you want to write to each LEDs

        CRGB currentPixel = wsledPixels[i];

        uint32_t packedData;
        if(type == WS2812B) { // different models have different color orders
            packedData = currentPixel.g | ((uint32_t)currentPixel.r << 8) | ((uint32_t)currentPixel.b << 16) | ((uint32_t)(0x00) << 24);
        } else {
            packedData = currentPixel.r | ((uint32_t)currentPixel.g << 8) | ((uint32_t)currentPixel.b << 16) | ((uint32_t)(0x00) << 24);
        }
        
        // Red
        dmaBuffer[n++] = timing_bits[0x0f & (packedData >> 4)];
        dmaBuffer[n++] = timing_bits[0x0f & (packedData)];

        // Green
        dmaBuffer[n++] = timing_bits[0x0f & (packedData >> 12)];
        dmaBuffer[n++] = timing_bits[0x0f & (packedData) >> 8];

        // Blue
        dma_buffer[n++] = timing_bits[0x0f & (packedData >> 20)];
        dma_buffer[n++] = timing_bits[0x0f & (packedData) >> 16];

    }

    // reset pulse
    for (int i = 0; i < resetDelay; i++) {
        dmaBuffer[n++] = 0;
    }

    esp_err_t error = spi_device_transmit(spi_settings.spi, &(spi_transaction_t) {
                                                    .length = dmaBufferSize * 8,
                                                    .tx_buffer = dmaBuffer,
                                                });
    return error;
}