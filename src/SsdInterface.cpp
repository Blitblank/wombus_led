
#include "SsdInterface.hpp"

SsdInterface::SsdInterface(const ssd_595_t* device, size_t numDigits) : device_(device), numDigits_(numDigits) {

    shiftInit(device_);

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