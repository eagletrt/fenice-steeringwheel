#!/bin/bash

#QMAKE="/home/$USER/Qt/5.10.1//gcc_64/bin/qmake"

QMAKE="/opt/Qt/5.10.1/gcc_64/bin/qmake"


QT_PROJECT="EagleSteeringWheel_x86.pro"
BUILD_DIR=build/

if [ ! "$( ls -A $BUILD_DIR)" ]; then
    mkdir $BUILD_DIR
fi

cd $BUILD_DIR

$QMAKE $QT_PROJECT -o Makefile ../$QT_PROJECT
make || exit 1

./EagleSteeringWheel_x86
