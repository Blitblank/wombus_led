
#include "WsledInterface.hpp"

WsledInterface::WsledInterface(const wsled_t* device) : device_(device), numLeds_(device->numLeds) {

    (void)wsledInit(device);

    // who cares if its dynamically allocated we have like 4 Mb of ram 
    // an led strip 1024 long will use 3kb here and 12kb in the driver for dma
    leds_.resize(numLeds_);

    // turn all leds off
    (void)fill(CRGB(0, 0, 0));
    (void)flush();

}

STATUS WsledInterface::writePixel(CRGB pixel, size_t index) {
    
    // is it really that easy
    leds_[index] = pixel;

    return OKAY;
}

STATUS WsledInterface::get(CRGB* pixel, size_t index) {

    // I could just return the pixel but im so cool and C coded
    *pixel = leds_[index];

    return OKAY;
}

STATUS WsledInterface::flush() {

    // man I wrote my driver so well that it really is that easy
    wsledUpdate(device_, leds_.data(), numLeds_);

    return OKAY;
}

STATUS WsledInterface::fill(CRGB color) {

    // I HATE ITERATORS YOU CAN NEVER MAKE ME USE THEM !!!!
    for (size_t i = 0; i < numLeds_; i++) {
        leds_[i] = color;
    }

    return OKAY;
}
