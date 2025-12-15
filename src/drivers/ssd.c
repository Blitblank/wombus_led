
#include "ssd.h"

#include "esp_rom_sys.h"
#include "esp_log.h"

#ifdef __cplusplus
extern "C" {
#endif

inline void pulse(gpio_num_t pin) {
    gpio_set_level(pin, 1);
    gpio_set_level(pin, 0);
}

void shiftInit(const ssd_595_t* device) {

    gpio_reset_pin(device->dataPin);
    gpio_reset_pin(device->clockPin);
    gpio_reset_pin(device->latchPin);

    gpio_config_t ioConfig = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << device->dataPin)  |
                        (1ULL << device->clockPin) |
                        (1ULL << device->latchPin),
    };
    gpio_config(&ioConfig);

    gpio_set_level(device->dataPin, 0);
    gpio_set_level(device->clockPin, 0);
    gpio_set_level(device->latchPin, 0);

    ESP_LOGI(__FILE__, "ssd_595 initialized");
}

void addDecimal(uint8_t* data) {
    // TODO: fix
    // data = (*data | 0x01);
}

void shiftByte(const ssd_595_t* device, uint8_t byte) {
    for(int i = 0; i < __CHAR_BIT__ ; i++) {
        uint32_t level = ((byte >> i) & 0x1) ^ device->commonCathode;
        gpio_set_level(device->dataPin, level);
        pulse(device->clockPin);
    }
    pulse(device->latchPin);
}

void shiftBytes(const ssd_595_t* device, uint8_t* bytes, size_t numBytes) {
    for(size_t i = 0; i < numBytes; i++) {
        shiftByte(device, bytes[i]);
    }
}

#ifdef __cplusplus
}
#endif
