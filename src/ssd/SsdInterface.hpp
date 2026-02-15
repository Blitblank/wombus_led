
#pragma once

#include "stdint.h"

#include "drivers/ssd.h"
#include "shared/common.h"

class SsdInterface {

public:

    SsdInterface(const ssd_595_t* device, size_t numDigits);
    ~SsdInterface() = default;

    // Outputs the data straight to hardware, mostly for testing purposes
    // bytes: the data to write, with bits targetting an led on the ssd
    // Returns: execution status
    STATUS writeRaw(uint8_t* bytes, size_t numBytes);

    // Displays a decimal integer on the ssd
    // value: the integer to display
    // Returns: execution status
    STATUS write10(int32_t value);

    // Displays a hexadecimal integer on the ssd
    // value: the integer to display
    // Returns: execution status
    STATUS write16(int32_t value);

    // Copies the data currently displayed on the ssd to bytes
    // bytes: place to write to
    // Returns: execution status
    STATUS get(uint8_t* bytes);

private:

    const ssd_595_t* device_;

    size_t numDigits_; // number of chained digits
    uint8_t* data_; // pointer to the data written

};
