
#!/usr/bin/env bash
set -e

export IDF_TOOLS_PATH=${PWD}/lib/idf-tools
export IDF_PATH=${PWD}/lib/esp-idf

export SDKCONFIG=${PWD}/config/sdkconfig
export SDKCONFIG_DEFAULTS=${PWD}/config/sdkconfig.defaults

. ${IDF_PATH}/export.sh

idf.py set-target esp32s3
idf.py build

# idk how to put it in the right place
mv ${PWD}/sdkconfig ${PWD}/config/sdkconfig
