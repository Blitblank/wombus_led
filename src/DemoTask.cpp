
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

    /*
    ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
    gpio_reset_pin(gpio_onboardLed);
    gpio_set_direction(gpio_onboardLed, GPIO_MODE_OUTPUT);

    while (1) {
        ESP_LOGI(TAG, "Turning the LED %s!", ledState == true ? "ON" : "OFF");
        gpio_set_level(gpio_onboardLed, ledState);
        ledState = !ledState;
        vTaskDelay(blinkTime / portTICK_PERIOD_MS);
    }
    */

    ESP_LOGI(__FILE__, "Demo Task");

    SsdInterface ssd(gpio_ssd_data, gpio_ssd_clk, gpio_ssd_latch, ssdDigits);
    uint32_t delay = 500; // ms
    uint8_t byte = 0x00;

    while(1) {
        ESP_LOGI(__FILE__, "Shifting out byte %02hhx", byte);

        ssd.writeRaw(&byte, 1);
        byte++;

        vTaskDelay(delay / portTICK_PERIOD_MS);
    }

}