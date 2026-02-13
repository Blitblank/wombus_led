
#include "WsledInterface.hpp"

WsledInterface::WsledInterface(const wsled_t* device) {

}

STATUS WsledInterface::writePixel(CRGB pixel, size_t index) {
    
    return OKAY;
}

STATUS WsledInterface::get(CRGB* pixel, size_t index) {

    return OKAY;
}

STATUS WsledInterface::flush() {

    return OKAY;
}
