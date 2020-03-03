#!/bin/bash

# This tool is used to deploy the application for raspberry pi 3 in desktop mode.
# Here you can find the variables get it from Qt Creator

#QMAKE="/home/$USER/Qt/5.10.1/gcc_64/bin/qmake"
QMAKE="/home/$USER/Qt/5.12.5/gcc_64/bin/qmake"
#QMAKE="/home/$USER/Qt/5.9.8/gcc_64/bin/qmake"

QT_PROJECT="eagleSteeringWheel.pro"
BUILD_DIR=build/

if [ ! "$( ls -A $BUILD_DIR)" ]; then
    mkdir $BUILD_DIR
fi

cd $BUILD_DIR

#socat -d -d pty,raw,nonblock,echo=0,link=ttyV0 pty,raw,nonblock,echo=0,link=ttyV1 &

$QMAKE $QT_PROJECT -o Makefile ../$QT_PROJECT
make || exit 1

./EagleSteeringWheel
