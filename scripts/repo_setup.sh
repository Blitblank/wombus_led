
#!/usr/bin/env bash
set -e

export IDF_TOOLS_PATH=${PWD}/lib/idf-tools
export IDF_PATH=${PWD}/lib/esp-idf

# if you get python ssl module errors- make sure your python version is 3.12 or lower

# esp-idf install scripts
bash ${IDF_PATH}/install.sh esp32s3
source ${IDF_PATH}/export.sh

# target
idf.py fullclean
idf.py set-target esp32s3
