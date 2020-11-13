#########################################################
#  _________ __                      .__                #
# /   _____//  |_  ____   ___________|__| ____    ____  #
# \_____  \\   __\/ __ \_/ __ \_  __ \  |/    \  / ___\ #
# /        \|  | \  ___/\  ___/|  | \/  |   |  \/ /_/  >#
#/_______  /|__|  \___  >\___  >__|  |__|___|  /\___  / #
#        \/           \/     \/              \//_____/  #
#########################################################

target.path = /root
INSTALLS   += target

QT += core gui qml quick serialbus opengl
CONFIG += qtquickcompiler

TARGET = FeniceSteeringWheel

INCLUDEPATH += . \
               lib/ \
               include/

HEADERS += include/buttons.h \
           include/control.h \
           include/errors.h \
           include/hv.h \
           include/inverters.h \
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
           include/graphics.h
 

SOURCES += src/main.cpp \
           src/buttons.cpp \
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
           src/graphics.cpp

RESOURCES += qml.qrc

LIBS += -L/usr/local/lib -lwiringPi
#LIBS += -Llib -lwiringPi
#INCLUDEPATH += /usr/local/include
