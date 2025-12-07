
file(GLOB SRC_FILES "*.c" "*.cpp")

idf_component_register(
    SRCS ${SRC_FILES}
    PRIV_REQUIRES spi_flash
    REQUIRES esp_driver_gpio
    INCLUDE_DIRS "."
)