#!/bin/bash

DEVELOPMENTDIR=~/Development
BBBGPIOPROJECT=BeagleBoneBlackGPIO
SMARTAQUARIUMPROJECT=SmartAquarium
MQTTCLIENTPROJECT=MQTTClient
REMOTEORIGIN=https://github.com/uilianries

for project in $BBBGPIOPROJECT $SMARTAQUARIUMPROJECT $MQTTCLIENTPROJECT
do
    projectdir=$DEVELOPMENTDIR/$project
    if [ ! -d $projectdir ]; then
        git clone $REMOTEORIGIN/$project.git $projectdir
    fi
done
