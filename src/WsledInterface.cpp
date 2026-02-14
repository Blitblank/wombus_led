
#include "WsledInterface.hpp"

WsledInterface::WsledInterface(const wsled_t* device) {

    (void)wsledInit(device);

}

STATUS WsledInterface::writePixel(CRGB pixel, size_t index) {
    
    leds_[index] = pixel;

    return OKAY;
}

STATUS WsledInterface::get(CRGB* pixel, size_t index) {

    *pixel = leds_[index];

    return OKAY;
}

STATUS WsledInterface::flush() {

    wsledUpdate(leds_, numLeds_);

    return OKAY;
}

STATUS WsledInterface::fill(CRGB color) {

    for (size_t i = 0; i < numLeds_; i++) {
        leds_[i] = color;
    }

    return OKAY;
}
