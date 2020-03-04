#########################################################
#  _________ __                      .__                #
# /   _____//  |_  ____   ___________|__| ____    ____  #
# \_____  \\   __\/ __ \_/ __ \_  __ \  |/    \  / ___\ #
# /        \|  | \  ___/\  ___/|  | \/  |   |  \/ /_/  >#
#/_______  /|__|  \___  >\___  >__|  |__|___|  /\___  / #
#        \/           \/     \/              \//_____/  #
#########################################################

TEMPLATE = app
TARGET = EagleSteeringWheel
INCLUDEPATH += . \
               lib/

QT += core gui qml quick serialbus
CONFIG += qtquickcompiler

# Input
HEADERS += header/buttons_x86.h \
           header/control.h \
           header/errors.h \
           header/hv.h \
           header/inverters.h \
           header/keypresseventfilter.h \
           header/console.h \
           header/canbus.h \
           header/carstatus.h \
           header/lv.h \
           header/manettini.h \
           header/race.h \
           header/sensors.h \
           header/telemetry.h \
           header/warning.h


SOURCES += core/main_x86.cpp \
           core/buttons_x86.cpp \
           core/keypresseventfilter.cpp \
           core/console.cpp \
           core/canbus.cpp \
           core/carstatus.cpp \
           core/inverters.cpp \
           core/control.cpp \
           core/race.cpp \
           core/warning.cpp \
           core/manettini.cpp \
           core/errors.cpp \
           core/sensors.cpp \
           core/hv.cpp \
           core/telemetry.cpp \
           core/lv.cpp

RESOURCES += qml.qrc
