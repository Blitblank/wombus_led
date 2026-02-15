
#pragma once

#include<stdint.h>

// This class is for managing tasks
class App {

public:

    App();
    ~App() = default;

    uint32_t main();

private:

    const char *TAG = "app"; // TODO: instead of this for logging you can use __FILE__ or __func__

};
