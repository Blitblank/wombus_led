
#include "App.hpp"

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "sdkconfig.h"

#include "pins.hpp"

App::App() {
    ESP_LOGI(TAG, "App constructor");
}

uint32_t App::main() {

    ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
    gpio_reset_pin(gpio_onboardLed);
    gpio_set_direction(gpio_onboardLed, GPIO_MODE_OUTPUT);

    while (1) {
        ESP_LOGI(TAG, "Turning the LED %s!", ledState == true ? "ON" : "OFF");
        gpio_set_level(gpio_onboardLed, ledState);
        /* Toggle the LED state */
        ledState = !ledState;
        vTaskDelay(blinkTime / portTICK_PERIOD_MS);
    }

    return 1; // unreachable
}
