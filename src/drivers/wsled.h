
#pragma once

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include <stdio.h>
#include <string.h>

#define WSLED_12_RESET_TIME 30
#define WSLED_15_RESET_TIME 30

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} CRGB;

typedef enum {
    WS2812B = 0,
    WS2815
} WsledType;

typedef struct {
    spi_host_device_t host;
    spi_device_handle_t spi;
    int dma_chan;
    spi_device_interface_config_t devcfg;
    spi_bus_config_t buscfg;
} spi_settings_t;

typedef struct {
    gpio_num_t pin;
    WsledType type;
    uint32_t numLeds;
} wsled_t;

esp_err_t wsledInit(wsled_t* dev, CRGB** buffer);

// test function
esp_err_t wsledFill(CRGB color);

esp_err_t wsledUpdate();

#ifdef __cplusplus
}
#endif
