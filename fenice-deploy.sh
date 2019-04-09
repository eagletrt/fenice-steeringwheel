#!/bin/bash

#new host
#root@eaglepi eaglepi

RASP_PI_ROOT=/mnt/rasp-pi-rootfs
RASP_PI_IMAGE=~/crosscompile-tools/raspbian.img
RASP_PI_QMAKE=/mnt/rasp-pi-rootfs/usr/local/qt5pi/bin/qmake
RASP_PI_PROJECT=FeniceSteeringWheel.pro
BUILD_DIR=build-fenice/
PI_ADDRESS=192.168.43.244
#PI_ADDRESS=root
DEPLOY_TARGET_DIR=/home/pi

# Mount image needed for crosscompilation dependencies
if [ ! "$(ls -A $RASP_PI_ROOT )" ]; then
    echo "E' Vuota!"
fi

if [ ! "$( ls -A $BUILD_DIR)" ]; then
    mkdir $BUILD_DIR
fi

cd $BUILD_DIR

#controlla su Qt Creator come compila lui
$RASP_PI_QMAKE -spec devices/linux-rasp-pi-g++ -o Makefile ../$RASP_PI_PROJECT
make -j4

scp EagleSteeringWheel root@$PI_ADDRESS:/

