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
            thirdparty/can/lib/

HEADERS += \
        include/car/interface.h \
        include/global.h \
        include/can/bus.h \
        include/can/device.h \
        include/car/das.h \
        include/car/hv.h \
        include/car/lv.h \
        include/car/inverters.h \
        include/car/state.h \
        include/car/steering.h \
        include/car/telemetry.h \
        include/io/buttons.h \
        include/io/leds.h \
        include/io/ptt.h \
        include/ui/emulator.h \
        include/ui/gameboy.h \
        include/ui/peanut.h \
        include/ui/speedometer.h \
        thirdparty/can/lib/primary/c/network.h \
        thirdparty/can/lib/secondary/c/network.h \
        thirdparty/can/lib/primary/c/watchdog.h \
        thirdparty/can/lib/secondary/c/watchdog.h \
        thirdparty/can/lib/primary/c/ids.h \
        thirdparty/can/lib/secondary/c/ids.h

SOURCES += \
        src/main.cpp \
        src/global.cpp \
        src/can/device.cpp \
        src/can/bus.cpp \
        src/car/das.cpp \
        src/car/hv.cpp \
        src/car/lv.cpp \
        src/car/inverters.cpp \
        src/car/state.cpp \
        src/car/steering.cpp \
        src/car/telemetry.cpp \
        src/ui/emulator.cpp \
        src/ui/gameboy.cpp \
        src/ui/speedometer.cpp


CONFIG(raspberry) {
SOURCES += \
        src/io/buttons.cpp \
        src/io/leds.cpp \
        src/io/ptt.cpp
DEFINES += S_OS_RASPBERRY
} else {
SOURCES += \
        src/io/buttons_x86.cpp \
        src/io/leds_x86.cpp \
        src/io/ptt_x86.cpp
DEFINES += S_OS_X86
}

DISTFILES += \
  qml/tabs/TabCalibration.qml \
  qml/tabs/components/CalibrationBar.qml
