
#include "DemoTask.hpp"

#include "esp_log.h"

#include "ssd/SsdInterface.hpp"
#include "wsled/WsledInterface.hpp"
#include "shared/pins.h"

#define NUM_LEDS 4

DemoTask::DemoTask() {

}

void DemoTask::run() {

    ESP_LOGI(__FILE__, "Demo Task: run()");

    // ssd device
    ssd_595_t ssdDev = { gpio_ssd_data, gpio_ssd_clk, gpio_ssd_latch, true };
    SsdInterface ssd(&ssdDev, ssdDigits);

    // wsled device
    wsled_t wsledDev = { gpio_ws2812b, WS2812B, NUM_LEDS};
    WsledInterface wsled(&wsledDev);

    uint32_t delay = 500; // ms
    uint8_t digit = 0;

    while(1) {
        ssd.writeRaw(&digitMap[digit], 1);
        digit++;
        if(digit >= 16) digit = 0;

        CRGB color = (digit % 2) ? CRGB{100, 20, 20} : CRGB{20, 20, 100};
        wsled.fill(color);
        wsled.flush();

        vTaskDelay(delay / portTICK_PERIOD_MS);
    }

}