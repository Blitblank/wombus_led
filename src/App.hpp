
#pragma once

#include<stdint.h>

class App {

public:

    App();
    ~App() = default;

    uint32_t main();

private:
    
    uint32_t ledState = 0;
    uint32_t blinkTime = 250;
    const char *TAG = "app";

};
