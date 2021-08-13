#########################################################
#  _________ __                      .__                #
# /   _____//  |_  ____   ___________|__| ____    ____  #
# \_____  \\   __\/ __ \_/ __ \_  __ \  |/    \  / ___\ #
# /        \|  | \  ___/\  ___/|  | \/  |   |  \/ /_/  >#
#/_______  /|__|  \___  >\___  >__|  |__|___|  /\___  / #
#        \/           \/     \/              \//_____/  #
#########################################################

QT += core gui qml quick serialbus
CONFIG += qtquickcompiler

TARGET = fenice-steering

OTHER_FILES += $$files("*.qml", true)

RESOURCES += qml.qrc

INCLUDEPATH += \
            . \
            include/ \
            thirdparty/can-cicd/naked_generator/ \
            thirdparty/can-cicd/includes_generator/

HEADERS += \
        include/steering.h \
        include/can/canbus.h \
        include/can/device.h \
        include/io/buttons.h \
        include/io/leds.h \
        include/steering.h \
        thirdparty/can-cicd/naked_generator/Primary/c/Primary.h \
        thirdparty/can-cicd/naked_generator/Secondary/c/Secondary.h \
        thirdparty/can-cicd/includes_generator/Primary/can_config.h \
        thirdparty/can-cicd/includes_generator/Primary/ids.h \
        thirdparty/can-cicd/includes_generator/Secondary/can_config.h \
        thirdparty/can-cicd/includes_generator/Secondary/ids.h

SOURCES += \
        src/main.cpp \
        src/steering.cpp \
        src/can/device.cpp \
        src/can/canbus.cpp \
        src/io/buttons_x86.cpp \
        src/io/leds_x86.cpp \
        thirdparty/can-cicd/naked_generator/Primary/c/Primary.c \
        thirdparty/can-cicd/naked_generator/Secondary/c/Secondary.c
