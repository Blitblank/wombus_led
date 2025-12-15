
#include "DemoTask.hpp"

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "SsdInterface.hpp"
#include "pins.hpp"

DemoTask::DemoTask() {

}

void DemoTask::run() {

    ESP_LOGI(__FILE__, "Demo Task: run()");

    ssd_595_t dev = { gpio_ssd_data, gpio_ssd_clk, gpio_ssd_latch, true };
    SsdInterface ssd(&dev, ssdDigits);

    uint32_t delay = 500; // ms
    uint8_t digit = 0;

    while(1) {
        ssd.writeRaw(&digitMap[digit], 1);
        digit++;
        if(digit >= 16) digit = 0;

        vTaskDelay(delay / portTICK_PERIOD_MS);
    }

}