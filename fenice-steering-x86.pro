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

INCLUDEPATH += . \
               lib/ \
               include/ \
               can-cicd/naked_generator/ \
               can-cicd/includes_generator/ 

# Input
HEADERS += include/buttons_x86.h \
           include/control.h \
           include/errors.h \
           include/hv.h \
           include/inverters.h \
           include/keypresseventfilter.h \
           include/console.h \
           include/canbus.h \
           include/carstatus.h \
           include/lv.h \
           include/manettini.h \
           include/race.h \
           include/sensors.h \
           include/telemetry.h \
           include/warning.h \
           include/detect.h \
           include/graphics.h \
           include/can/can.h \
           can-cicd/naked_generator/Primary/c/Primary.h \
           can-cicd/naked_generator/Secondary/c/Secondary.h \
           can-cicd/includes_generator/Primary/can_config.h \
           can-cicd/includes_generator/Primary/ids.h \
           can-cicd/includes_generator/Secondary/can_config.h \
           can-cicd/includes_generator/Secondary/ids.h 

SOURCES += src/main_x86.cpp \
           src/buttons_x86.cpp \
           src/keypresseventfilter.cpp \
           src/console.cpp \
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
           src/graphics.cpp \
           can-cicd/naked_generator/Primary/c/Primary.c \
           can-cicd/naked_generator/Secondary/c/Secondary.c

RESOURCES += qml.qrc
