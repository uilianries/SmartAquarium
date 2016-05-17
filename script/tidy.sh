#!/bin/bash

linter=clang-tidy-3.6
log_file=script/tidy.log
target=$(find src test -type f -name "*pp")

if [[ $# -eq 0 ]]; then
    echo "WARNING: Input is empty, using default target: ${target}"
else
    eval target="$@"
fi

check_program() {
    if hash ${linter} 2>/dev/null; then
        echo "INFO: Check programmer errors (Linter)"
    else
        echo "ERROR: Could not find ${linter}. Please, check if is installed"
        exit 1
    fi
}

execute_linter() {
    ${linter} -checks='*,-clang-analyzer-alpha.deadcode.UnreachableCode,-google-explicit-constructor' ${target} -- -std=c++11 -Wall -Wextra -Werror -Wshadow -Itest -Isrc -I. &> ${log_file}

    cat ${log_file}
    fgrep "warning:" ${log_file}
    if [ $? -eq 0 ]; then
        echo "ERROR: Linter found some warning"
        exit 1
    fi
}

main() {
    check_program
    execute_linter
}

main
