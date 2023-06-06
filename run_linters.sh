#!/bin/bash


#!/bin/bash
set -o pipefail

function check_log() {
    LOG=$( { ${1}; } 2>&1 )
    STATUS=$?
    echo "$LOG"
    if echo "$LOG" | grep -q -E "${2}"
    then
        exit 1
    fi

    if [ $STATUS -ne 0 ]
    then
        exit $STATUS
    fi
}

echo -e "\nRun linters"

echo -e "\nRUN cpplint.py"
check_log "cpplint --extensions=cpp,hpp --recursive ./server/* ./client/*" "Can't open for reading"

echo - e "\nRUN cppcheck"
check_log "cppcheck server --std=c++17 --enable=all" "\(information\)"

echo -e "SUCCESS"