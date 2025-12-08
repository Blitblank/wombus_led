
#include "ssd.h"

void shiftInit(const ssd_595_t* device) {
    gpio_config_t ioConfig = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << device->dataPin)  |
                        (1ULL << device->clockPin) |
                        (1ULL << device->latchPin)
    };
    gpio_config(&ioConfig);

    gpio_set_level(device->dataPin, 0);
    gpio_set_level(device->clockPin, 0);
    gpio_set_level(device->latchPin, 0);
}

void addDecimal(uint8_t* data) {
    data = (*data | 0x01);
}

void shiftByte(const ssd_595_t* device, uint8_t byte) {
    for(int i = 0; i < __CHAR_BIT__; i++) {
        gpio_set_level(device->dataPin, (byte >> i) & 0x1);
        pulse(device->clockPin);
    }
    pulse(device->latchPin);
}

void shiftBytes(const ssd_595_t* device, uint8_t* bytes, size_t numBytes) {
    for(size_t i = 0; i < numBytes; i++) {
        shiftByte(device, bytes[i]);
    }
}