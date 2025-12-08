
#pragma once

#include "drivers/ssd.h"
#include "stdint.h"

class SsdInterface {

public:

    SsdInterface();
    ~SsdInterface() = default;

    uint32_t write(int32_t value, bool hex); // hex=false => decimal 
    uint32_t write(int32_t value, uint32_t decimal);

private:



};
