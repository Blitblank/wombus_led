
#include "wsled.h"

#include "esp_heap_caps.h"
#include "esp_log.h"

#ifdef __cplusplus
extern "C" {
#endif

static uint16_t* dmaBuffer;
static size_t dmaBufferSize;

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

// translations from SPI -> ws2812b protocol
// [spi] 0b1110 = [ws2812b]0b1 and [spi] 0b1000 = [ws2812b]0b0
static const uint16_t timingBits[16] = {
    0x1111, 0x7111, 0x1711, 0x7711, 0x1171, 0x7171, 0x1771, 0x7771,
    0x1117, 0x7117, 0x1717, 0x7717, 0x1177, 0x7177, 0x1777, 0x7777};

// WS2812b can handle shorter reset delays than the WS2815
static inline uint32_t resetDelay(const wsled_t* dev) {
    return (dev->type == WS2812B) ? WSLED_12_RESET_TIME : WSLED_15_RESET_TIME;
}

esp_err_t wsledInit(const wsled_t* dev) {

    // 12 bytes for each led + bytes for initial zero and reset state
    dmaBufferSize = dev->numLeds * 12 + (resetDelay(dev) + 1) * 2;

    spiSettings.buscfg.mosi_io_num = dev->pin;
    spiSettings.buscfg.max_transfer_sz = dmaBufferSize;

    if (ESP_OK != spi_bus_initialize(spiSettings.host, &spiSettings.buscfg, spiSettings.dma_chan)) {
        ESP_LOGI(__FILE__, "SPI initialization failed");
        return -1;
    }

    if (ESP_OK != spi_bus_add_device(spiSettings.host, &spiSettings.devcfg, &spiSettings.spi)) {
        ESP_LOGI(__FILE__, "Failed to add spi bus device");
        return -1;
    }

    dmaBuffer = heap_caps_malloc(dmaBufferSize, MALLOC_CAP_DMA);
    if (NULL == dmaBuffer) {
        ESP_LOGI(__FILE__, "Failed to heap_caps_malloc");
        return -1;
    }
    return ESP_OK;
}

esp_err_t wsledUpdate(const wsled_t* dev, const CRGB* pixels, size_t ledCount) {

    uint32_t n = 0;

    memset(dmaBuffer, 0, dmaBufferSize);
    dmaBuffer[n++] = 0;

    for (int i = 0; i < ledCount; i++) {

        CRGB currentPixel = pixels[i];

        uint8_t b0 = (dev->type == WS2812B) ? currentPixel.g : currentPixel.r;
        uint8_t b1 = (dev->type == WS2812B) ? currentPixel.r : currentPixel.g;
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
    for (int i = 0; i < resetDelay(dev); i++) {
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
