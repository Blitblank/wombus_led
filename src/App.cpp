
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

    ESP_LOGI(__FILE__, "Running App::main()");

    static DemoTask demoTask{};

    ESP_LOGI(__FILE__, "Starting DemoTask");
    demoTask.start("DemoTask", 4096, 5, 1);

    return 1;
}
