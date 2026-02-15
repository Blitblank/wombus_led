
#include "DemoTask.hpp"

#include "esp_log.h"

#include "ssd/SsdInterface.hpp"
#include "wsled/WsledInterface.hpp"
#include "shared/pins.h"

DemoTask::DemoTask() {

}

void DemoTask::run() {

    ESP_LOGI(__FILE__, "Demo Task: run()");

    // ssd device
    ssd_595_t ssdDev = { gpio_ssd_data, gpio_ssd_clk, gpio_ssd_latch, true };
    SsdInterface ssd(&ssdDev, ssdDigits);

    // wsled device
    wsled_t wsledDev = { gpio_ws2812b, WS2812B, 0 /* fixed */};
    WsledInterface wsled(&wsledDev);

    uint32_t delay = 500; // ms
    uint8_t digit = 0;

    while(1) {
        ssd.writeRaw(&digitMap[digit], 1);
        digit++;
        if(digit >= 16) digit = 0;

        wsled.fill(CRGB{100, 20, 20});
        wsled.flush();

        vTaskDelay(delay / portTICK_PERIOD_MS);

        wsled.fill(CRGB{20, 20, 100});
        wsled.flush();

        vTaskDelay(delay / portTICK_PERIOD_MS);
    }

}