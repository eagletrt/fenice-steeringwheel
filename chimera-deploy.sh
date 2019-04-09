#!/bin/bash

CHIMERA_QMAKE=/opt/Qt/5.10.1/Boot2Qt/raspberrypi3/toolchain/sysroots/x86_64-pokysdk-linux/usr/bin/qmake 
CHIMERA_PROJECT=ChimeraSteeringWheel.pro
CHIMERA_SPECS=-spec devices/linux-rasp-pi-g++ #&& /usr/bin/make qmake_all
BUILD_DIR=build-chimera/
CHIMERA_ADDRESS=192.168.43.244
DEPLOY_TARGET_DIR=/home/pi

if [ ! "$( ls -A $BUILD_DIR)" ]; then
    mkdir $BUILD_DIR
fi

cd $BUILD_DIR

$RASP_PI_QMAKE $RASP_PI_PROJECT $CHIMERA_SPECS
make -j4 || exit 1

# Upload executable on the Rasp
#scp ChimeraSteeringWheel root@$PI_ADDRESS:/

