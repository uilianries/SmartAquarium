#!/bin/bash

read_temperature() {
  temperature=$(cat /sys/bus/w1/devices/28-*/w1_slave | grep -E 't=\w{3,6}' | grep -oE '\w{3,6}')
  if [ ${#temperature} -lt 4 ]; then
    return
  fi
  dot=$(expr ${#temperature} - 3)
  result=${temperature:0:$dot}.${temperature:$dot}
  logger -t "smartaquarium" "Current temperature: $resultºC"
  mosquitto_pub -h m11.cloudmqtt.com -p 15347 -u temperature_sensor -P temperaturesensor -t smartaquarium/sensor/temperature/level -m $result
}
main() {

  while [ 1 ]; do
    read_temperature
    sleep 10
  done
}

main