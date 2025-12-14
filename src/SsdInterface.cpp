
#include "SsdInterface.hpp"

SsdInterface::SsdInterface(const uint8_t dataPin, const uint8_t clockPin, const uint8_t latchPin, size_t numDigits) : numDigits_(numDigits) {

    // create device
    static ssd_595_t dev = { (gpio_num_t)dataPin, (gpio_num_t)clockPin, (gpio_num_t)latchPin };
    device_ = &dev;

}

STATUS SsdInterface::writeRaw(uint8_t* bytes, size_t numBytes) {
    shiftBytes(device_, bytes, numBytes);
    return OKAY;
}

STATUS SsdInterface::write10(int32_t value) {
    // TODO: implement
    return NOT_IMPLEMENTED;
}

STATUS SsdInterface::write16(int32_t value) {
    // TODO: implement
    return NOT_IMPLEMENTED;
}

STATUS SsdInterface::get(uint8_t* bytes) {
    // TODO: implement
    return NOT_IMPLEMENTED;
}