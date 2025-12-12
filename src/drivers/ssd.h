
#include <stdint.h>
#include "driver/gpio.h"

typedef struct {
    gpio_num_t dataPin;
    gpio_num_t clockPin;
    gpio_num_t latchPin;
} ssd_595_t;

uint8_t map[17] = { // encoding of digits on the seven segment display
    0xFC, // 0
    0x60, // 1
    0xDA, // 2
    0xF2, // 3
    0x66, // 4
    0xB6, // 5
    0xBE, // 6
    0xE0, // 7
    0xFE, // 8
    0xF6, // 9
    0xEE, // A
    0x3E, // B
    0x9C, // C
    0x7A, // D
    0x9E, // E
    0x8E, // F
    0x02, // -
};

void shiftInit(const ssd_595_t* device);
void pulse(gpio_num_t pin);

void addDecimal(uint8_t* data); // adds a decimal to a single digit

void shiftByte(const ssd_595_t* device, uint8_t byte); // outputs a serial byte, big-endian
void shiftBytes(const ssd_595_t* device, uint8_t* bytes, size_t numBytes); // outputs multiple bytes

