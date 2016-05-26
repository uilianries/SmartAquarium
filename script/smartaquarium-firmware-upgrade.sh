#!/bin/bash

DEVELOPMENTDIR=~/Development
BBBGPIOPROJECT=BeagleBoneBlackGPIO
SMARTAQUARIUMPROJECT=SmartAquarium
MQTTCLIENTPROJECT=MQTTClient
UPGRADE=0

for project in $BBBGPIOPROJECT $SMARTAQUARIUMPROJECT $MQTTCLIENTPROJECT
do
    projectdir=$DEVELOPMENTDIR/$project
    cd $projectdir
    currentcommit=$(git rev-parse --verify HEAD)
    git pull
    newcommit=$(git rev-parse --verify HEAD)
    if [ "$currentcommit" != "$newcommit" ]; then
        let UPGRADE=1
    fi
done

if [ $UPGRADE -eq 1 ]; then
    for project in $BBBGPIOPROJECT $MQTTCLIENTPROJECT $SMARTAQUARIUMPROJECT
    do
        projectdir=$DEVELOPMENTDIR/$project
        builddir=$projectdir/build
        cd $projectdir
        if [ -d $builddir ]; then
            rm -rf $builddir/*
        else
            mkdir $builddir
        fi
        cd $builddir
        cmake .. -DCMAKE_BUILD_TYPE=Release
        cmake --build .
        if [ $? -ne 0 ]; then
            echo "ERROR: Could not build project $project"
            exit 1
        fi

        cd ..
        script/tier_one.sh
        if [ $? -ne 0 ]; then
            echo "ERROR: Tier 1 fail on project $project"
            exit 1
        fi

        cd $builddir
        sudo make install
        if [ $? -ne 0 ]; then
            echo "ERROR: Could not install project $project"
            exit 1
        fi
    done
fi
