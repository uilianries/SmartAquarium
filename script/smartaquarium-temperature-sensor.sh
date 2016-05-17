#!/bin/bash

read_temperature() {
  temperature=$(cat /sys/bus/w1/devices/28-00000609893b/w1_slave | grep -E 't=\w{3,6}' | grep -oE '\w{3,6}')
  dot=$(expr ${#temperature} - 3)
  result=${temperature:0:$dot}.${temperature:$dot}
  return result
}

publish_temperature() {
  mosquitto_pub -h m11.cloudmqtt.com -p 15347 -u temperature_sensor -P temperaturesensor -t smartaquarium/sensor/temperature/level -m $1
}

main() {

  while [ 1 ]; do
    temperature=read_temperature
    publish_temperature $temperature
  done
}

main
