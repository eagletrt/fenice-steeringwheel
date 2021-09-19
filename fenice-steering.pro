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
        include/global.h \
        include/can/bus.h \
        include/can/device.h \
        include/can/primary.h \
        include/can/secondary.h \
        include/car/ecu.h \
        include/car/hv.h \
        include/car/lv.h \
        include/car/inverters.h \
        include/car/pedals.h \
        include/car/state.h \
        include/car/steering.h \
        include/car/telemetry.h \
        include/game/gb.h \
        include/game/extension.h \
        include/io/buttons.h \
        include/io/leds.h \
        thirdparty/can-cicd/naked_generator/Primary/c/Primary.h \
        thirdparty/can-cicd/naked_generator/Secondary/c/Secondary.h \
        thirdparty/can-cicd/includes_generator/Primary/can_config.h \
        thirdparty/can-cicd/includes_generator/Primary/ids.h \
        thirdparty/can-cicd/includes_generator/Secondary/can_config.h \
        thirdparty/can-cicd/includes_generator/Secondary/ids.h

SOURCES += \
        src/main.cpp \
        src/global.cpp \
        src/can/device.cpp \
        src/can/bus.cpp \
        src/car/ecu.cpp \
        src/car/hv.cpp \
        src/car/lv.cpp \
        src/car/inverters.cpp \
        src/car/pedals.cpp \
        src/car/state.cpp \
        src/car/steering.cpp \
        src/car/telemetry.cpp \
        src/game/gb.cpp \
        src/game/extension.cpp \
        thirdparty/can-cicd/naked_generator/Primary/c/Primary.c \
        thirdparty/can-cicd/naked_generator/Secondary/c/Secondary.c


CONFIG(raspberry) {
SOURCES += \
        src/io/buttons.cpp \
        src/io/leds.cpp 
DEFINES += S_OS_RASPBERRY
} else {
SOURCES += \
        src/io/buttons_x86.cpp \
        src/io/leds_x86.cpp 
DEFINES += S_OS_X86
}

DISTFILES += \
    qml/tabs/TabGame.qml
