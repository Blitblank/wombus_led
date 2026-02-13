
#include "wsled.h"

#include "esp_heap_caps.h"
#include "esp_log.h"

#ifdef __cplusplus
extern "C" {
#endif

uint16_t* dmaBuffer;
CRGB* wsledPixels;
static uint32_t ledCount;
static uint32_t resetDelay;
static size_t dmaBufferSize;
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
            //.flags = SPI_DEVICE_TXBIT_LSBFIRST,
        },
};

static const uint16_t timingBits[16] = {
    0x1111, 0x7111, 0x1711, 0x7711, 0x1171, 0x7171, 0x1771, 0x7771,
    0x1117, 0x7117, 0x1717, 0x7717, 0x1177, 0x7177, 0x1777, 0x7777};

esp_err_t wsledInit(wsled_t* dev, CRGB** buffer) {

    ESP_LOGI(__FILE__, "Initializing wsled device...");

    type = dev->type;
    ledCount = dev->numLeds;
    resetDelay = (dev->type == WS2812B) ? WSLED_12_RESET_TIME : WSLED_15_RESET_TIME;

    ESP_LOGI(__FILE__, "mallocing the wsledPixel buffer with size %u bytes", sizeof(CRGB) * ledCount);

    // 12 bytes for each led + bytes for initial zero and reset state
    dmaBufferSize = ledCount * 12 + (resetDelay + 1) * 2;
    wsledPixels = malloc(sizeof(CRGB) * ledCount);
    if (wsledPixels == NULL) {
        ESP_LOGI(__FILE__, "Allocating memory failed");
        return ESP_ERR_NO_MEM;
    }
    *buffer = wsledPixels;
    spiSettings.buscfg.mosi_io_num = dev->pin;
    spiSettings.buscfg.max_transfer_sz = dmaBufferSize;

    ESP_LOGI(__FILE__, "Initializing spi interface...");
    if (ESP_OK != spi_bus_initialize(spiSettings.host, &spiSettings.buscfg, spiSettings.dma_chan)) {
        free(wsledPixels);
        ESP_LOGI(__FILE__, "SPI initialization failed");
        return -1;
    }

    ESP_LOGI(__FILE__, "Adding spi bus device...");
    if (ESP_OK != spi_bus_add_device(spiSettings.host, &spiSettings.devcfg, &spiSettings.spi)) {
        free(wsledPixels);
        ESP_LOGI(__FILE__, "Failed to add spi bus device");
        return -1;
    }

    ESP_LOGI(__FILE__, "heap_caps_malloc() with dmaBufferSize=%u...", dmaBufferSize);
    dmaBuffer = heap_caps_malloc(dmaBufferSize, MALLOC_CAP_DMA);
    if (NULL == dmaBuffer) {
        free(wsledPixels);
        ESP_LOGI(__FILE__, "Failed to heap_caps_malloc");
        return -1;
    }
    return ESP_OK;
}

esp_err_t wsledFill(CRGB color) {
    for (int i = 0; i < ledCount; i++) {
        wsledPixels[i] = color;
    }
    return 0;
}

esp_err_t wsledUpdate() {

    uint32_t n = 0;

    memset(dmaBuffer, 0, dmaBufferSize);
    dmaBuffer[n++] = 0;

    for (int i = 0; i < ledCount; i++) {

        CRGB currentPixel = wsledPixels[i];

        uint8_t b0 = (type == WS2812B) ? currentPixel.g : currentPixel.r;
        uint8_t b1 = (type == WS2812B) ? currentPixel.r : currentPixel.g;
        uint8_t b2 = currentPixel.b;

        // Green
        dmaBuffer[n++] = timingBits[(b0 >> 4) & 0x0F];
        dmaBuffer[n++] = timingBits[b0 & 0x0F];

        // Red
        dmaBuffer[n++] = timingBits[(b1 >> 4) & 0x0F];
        dmaBuffer[n++] = timingBits[b1 & 0x0F];

        // Blue
        dmaBuffer[n++] = timingBits[(b2 >> 4) & 0x0F];
        dmaBuffer[n++] = timingBits[b2 & 0x0F];

    }

    // reset pulse
    for (int i = 0; i < resetDelay; i++) {
        dmaBuffer[n++] = 0;
    }

    esp_err_t error = spi_device_transmit(spiSettings.spi, &(spi_transaction_t) {
                                                    .length = dmaBufferSize * 8,
                                                    .tx_buffer = dmaBuffer,
                                                });
    return error;
}

#ifdef __cplusplus
}
#endif
