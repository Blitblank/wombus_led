
#include "DemoTask.hpp"

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "SsdInterface.hpp"
#include "pins.hpp"
#include "drivers/wsled.h"

DemoTask::DemoTask() {

}

void DemoTask::run() {

    ESP_LOGI(__FILE__, "Demo Task: run()");

    // ssd device
    ssd_595_t ssdDev = { gpio_ssd_data, gpio_ssd_clk, gpio_ssd_latch, true };
    SsdInterface ssd(&ssdDev, ssdDigits);

    // wsled device
    size_t ledCount = 4;
    wsled_t wsledDev = { gpio_ws2812b, WS2812B, ledCount};
    // TODO: wsled interface
    CRGB ledBuffer[4];
    wsledInit(&wsledDev, (CRGB**)&ledBuffer);

    uint32_t delay = 500; // ms
    uint8_t digit = 0;

    while(1) {
        ssd.writeRaw(&digitMap[digit], 1);
        digit++;
        if(digit >= 16) digit = 0;

        //ledBuffer[0] = CRGB{100, 0, 80};
        wsledFill(CRGB{100, 20, 20});
        wsledUpdate();

        vTaskDelay(delay / portTICK_PERIOD_MS);

        //ledBuffer[0] = CRGB{0, 0, 10};
        wsledFill(CRGB{20, 20, 100});
        wsledUpdate();

        vTaskDelay(delay / portTICK_PERIOD_MS);
    }

}