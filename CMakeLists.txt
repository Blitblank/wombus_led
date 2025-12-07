
cmake_minimum_required(VERSION 3.16)

set(PROJECT_MAIN_COMPONENT ${CMAKE_CURRENT_LIST_DIR}/src)
set(EXTRA_COMPONENT_DIRS ${CMAKE_CURRENT_LIST_DIR}/src)

# For the esp-idf configuration
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(wombus_led)
