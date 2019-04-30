#!/bin/bash

# This tool is used to deploy the application for raspberry pi 3. 
# Here you can find the variables get it from Qt Creator
# The script is divided in 2 parts, the compilation and the export via scp to the target

#lucagump
#CHIMERA_QMAKE=/opt/Qt/5.10.1/Boot2Qt/raspberrypi3/toolchain/sysroots/x86_64-pokysdk-linux/usr/bin/qmake
#EagleTRT-LAB
CHIMERA_QMAKE=/home/eagletrt/Qt/5.10.1/Boot2Qt/raspberrypi3/toolchain/sysroots/x86_64-pokysdk-linux/usr/bin/qmake 

CHIMERA_SPECS=-spec devices/linux-rasp-pi-g++ && /usr/bin/make qmake_all
CHIMERA_PROJECT=ChimeraSteeringWheel.pro
BUILD_DIR=build-chimera/

APP=steering
CHIMERA_ADDRESS=192.168.43.244
DEPLOY_TARGET_DIR=/

if [ ! "$( ls -A $BUILD_DIR)" ]; then
    mkdir $BUILD_DIR
fi

cd $BUILD_DIR
$CHIMERA_QMAKE ../$CHIMERA_PROJECT $CHIMERA_SPECS && $CHIMERA_MAKE
make -j8 || exit 1

# Upload executable on the Rasp
scp $APP root@$CHIMERA_ADDRESS:$DEPLOY_TARGET_DIR

