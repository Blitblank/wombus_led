
#!/usr/bin/env bash
set -e

export IDF_TOOLS_PATH=${PWD}/lib/idf-tools
export IDF_PATH=${PWD}/lib/esp-idf

export IDF_PATH_FORCE=1
. ${IDF_PATH}/export.sh

idf.py -b 115200 monitor

# idf.py autodetects port but use -p <port> to specify