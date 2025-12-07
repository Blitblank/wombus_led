
#!/usr/bin/env bash
set -e

export IDF_TOOLS_PATH=${PWD}/lib/idf-tools
export IDF_PATH=${PWD}/lib/esp-idf

. ${IDF_PATH}/export.sh

idf.py fullclean
idf.py set-target esp32s3
idf.py -b 115200 flash

# idf.py autodetects port but use -p <port> to specify

# idk how to put it in the right place
mv ${PWD}/sdkconfig ${PWD}/config/sdkconfig
