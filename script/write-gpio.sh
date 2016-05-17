#!/bin/bash

fake_gpio_path=/var/tmp/fake_gpio

warning () {
  echo "Usage: $0 -l|--level <value>"
  exit 1
}

if [ $# -ne 2 ]
then
  warning
fi

case $1 in
  -l|--level)
  echo $2 > $fake_gpio_path
  exit 0
  ;;
*)
  warning
  ;;
esac
