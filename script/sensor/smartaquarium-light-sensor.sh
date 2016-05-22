#!/bin/bash

read_light() {
        raw_level=$(cat /sys/devices/ocp.*/helper.*/AIN1)
        percent_level=$(expr ${raw_level} \* 100 / 1700)
        logger -t "smartaquarium"  "Current light emission: ${percent_level}%"
        mosquitto_pub -h m11.cloudmqtt.com -p 15347 -u light_sensor -P lightsensor -t smartaquarium/sensor/light/level -m ${percent_level}
}

main() {
        while [ 1 ]; do
                read_light
                sleep 10
        done
}

main