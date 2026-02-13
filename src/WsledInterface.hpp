
#pragma once

#include "stdint.h"

#include "drivers/wsled.h"
#include "common.h"

class WsledInterface {

public:

    WsledInterface(const wsled_t* device);
    ~WsledInterface() = default;

    // Sets a pixel in the leds buffer to a particular color
    // index: the order in the strip of the pixel
    // Returns: execution status
    STATUS writePixel(CRGB pixel, size_t index);

    // Copies the color currently in a pixel to the pointer
    // index: the order in the strip of the pixel 
    // Returns: execution status
    STATUS get(CRGB* pixel, size_t index);

    // Writes all the data in the leds buffer to hardware
    // Returns: execution status
    STATUS flush();

private:

    const wsled_t* device_;

    static constexpr size_t numLeds_ = 4;

    CRGB leds_[numLeds_];

};
