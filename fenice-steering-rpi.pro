#########################################################
#  _________ __                      .__                #
# /   _____//  |_  ____   ___________|__| ____    ____  #
# \_____  \\   __\/ __ \_/ __ \_  __ \  |/    \  / ___\ #
# /        \|  | \  ___/\  ___/|  | \/  |   |  \/ /_/  >#
#/_______  /|__|  \___  >\___  >__|  |__|___|  /\___  / #
#        \/           \/     \/              \//_____/  #
#########################################################

target.path = /home/pi
INSTALLS   += target

QT += core gui qml quick serialbus
CONFIG += qtquickcompiler

TARGET = fenice-steering

OTHER_FILES += $$files("*.qml", true)

RESOURCES += qml.qrc

LIBS += -L/usr/local/lib -lwiringPi

INCLUDEPATH += \
            . \
            include/ \
            thirdparty/can-cicd/naked_generator/ \
            thirdparty/can-cicd/includes_generator/ \
            thirdparty/wiringpi/wiringPi

HEADERS += \
        include/buttons.h \
        include/control.h \
        include/errors.h \
        include/hv.h \
        include/inverters.h \
        include/canbus.h \
        include/carstatus.h \
        include/leds.h \
        include/lv.h \
        include/manettini.h \
        include/race.h \
        include/sensors.h \
        include/steering.h \
        include/telemetry.h \
        include/warning.h \
        include/detect.h \
        include/can/primary.h \
        include/can/secondary.h \
        thirdparty/can-cicd/naked_generator/Primary/c/Primary.h \
        thirdparty/can-cicd/naked_generator/Secondary/c/Secondary.h \
        thirdparty/can-cicd/includes_generator/Primary/can_config.h \
        thirdparty/can-cicd/includes_generator/Primary/ids.h \
        thirdparty/can-cicd/includes_generator/Secondary/can_config.h \
        thirdparty/can-cicd/includes_generator/Secondary/ids.h
 

SOURCES += \
        src/main.cpp \
        src/buttons.cpp \
        src/canbus.cpp \
        src/carstatus.cpp \
        src/inverters.cpp \
        src/control.cpp \
        src/race.cpp \
        src/warning.cpp \
        src/manettini.cpp \
        src/errors.cpp \
        src/sensors.cpp \
        src/hv.cpp \
        src/telemetry.cpp \
        src/lv.cpp \
        src/detect.cpp \
        src/leds.cpp \
        thirdparty/can-cicd/naked_generator/Primary/c/Primary.c \
        thirdparty/can-cicd/naked_generator/Secondary/c/Secondary.c
