
#include "driver/gpio.h"

// onboard led
const gpio_num_t gpio_onboardLed = GPIO_NUM_2;

// misc
const gpio_num_t gpio_msdDetect  = GPIO_NUM_8;
const gpio_num_t gpio_ws2812b    = GPIO_NUM_9;

// i2c
const gpio_num_t gpio_i2c_dout   = GPIO_NUM_11;
const gpio_num_t gpio_i2c_din    = GPIO_NUM_12;

// i2c expander interrupts
const gpio_num_t gpio_i2c_intrA  = GPIO_NUM_14;
const gpio_num_t gpio_i2c_intrB  = GPIO_NUM_13;

// uart
const gpio_num_t gpio_uart_rx    = (gpio_num_t)44; // should already be configured
const gpio_num_t gpio_uart_tx    = (gpio_num_t)43; // should already be configured

// seven segment display
const gpio_num_t gpio_ssd_latch  = GPIO_NUM_17;
const gpio_num_t gpio_ssd_clk    = GPIO_NUM_18;
const gpio_num_t gpio_ssd_data   = GPIO_NUM_21;

// i2s
const gpio_num_t gpio_i2s_wsel   = GPIO_NUM_38;
const gpio_num_t gpio_i2s_din    = GPIO_NUM_39;
const gpio_num_t gpio_i2s_bck    = (gpio_num_t)40; // idk why it only goes up to 40
const gpio_num_t gpio_i2s_mck    = (gpio_num_t)41;
const gpio_num_t gpio_i2s_mute   = (gpio_num_t)42;
const gpio_num_t gpio_i2s_shdn   = (gpio_num_t)45;
