
#include "App.hpp"

#include "esp_log.h"

static const char *TAG = "main";

#ifdef __cplusplus
extern "C" {
#endif

void app_main(void) {

    ESP_LOGI(TAG, "Program start");

    App app;
    int32_t status = app.main();
    ESP_LOGI(TAG, "App main returned status %d", status);
}

#ifdef __cplusplus
}
#endif
