
#include "App.hpp"

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sdkconfig.h"

#include "pins.hpp"

#include "DemoTask.hpp"

App::App() {
    ESP_LOGI(TAG, "App constructor");
}

uint32_t App::main() {

    DemoTask demoTask{};

    demoTask.start("BlinkTask", 2048, 5, 1);

    return 1;
}
