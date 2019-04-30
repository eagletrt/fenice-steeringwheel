#!/bin/bash

# This tool is used to deploy the application for raspberry pi 3 in desktop mode. 
# Here you can find the variables get it from Qt Creator

#EagleTRT-LAB
QMAKE="/home/$USER/Qt/5.10.1//gcc_64/bin/qmake"

#lucagump
#QMAKE="/opt/Qt/5.10.1/gcc_64/bin/qmake"

QT_PROJECT="EagleSteeringWheel_x86.pro"
BUILD_DIR=build/

if [ ! "$( ls -A $BUILD_DIR)" ]; then
    mkdir $BUILD_DIR
fi

cd $BUILD_DIR

$QMAKE $QT_PROJECT -o Makefile ../$QT_PROJECT
make || exit 1

./EagleSteeringWheel_x86
