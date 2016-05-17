#!/bin/bash

log_file='valgrind.log'

if [[ $# -eq 0 ]]; then
    echo "ERROR: Input is empty"
    echo "usage: $0 <executable-file>"
else
    eval target=$1
fi

if [ ! -e ${target} ]; then
    echo "ERROR: ${target} is an invalid path."
    exit 1
fi

if hash valgrind 2>/dev/null; then
    echo "INFO: Memory leak check (Valgrind)"
else
    echo "ERROR: Could not find valgrind. Please, check if is installed"
    exit 1
fi

valgrind --tool=memcheck --leak-check=full ${target} &> ${log_file}

cat ${log_file}

fgrep 'definitely lost: 0 bytes in 0 blocks' ${log_file}
if [ $? -ne 0 ]; then
    echo "ERROR: Unit Test failed"
    exit 1
else
    echo "INFO: Unit test finished with success"
fi

exit 0
