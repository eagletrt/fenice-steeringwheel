# _________   ___ ___ .__   _____        __________         
# \_   ___ \ /   |   \|__| /     \   ____\______   \_____   
# /    \  \//    ~    \  |/  \ /  \_/ __ \|       _/\__  \  
# \     \___\    Y    /  /    Y    \  ___/|    |   \ / __ \_
#  \______  /\___|_  /|__\____|__  /\___  >____|_  /(____  /
#         \/       \/            \/     \/       \/      \/ 

# This file contains all the messages 
# neeeded to test the fsm of the steering 
# and the data visualization functionality

# Speed

    m_speed = ((uint8_t)val1 * 256 + (uint8_t)val2) / 10;

    cansend vcan0 0D0#06 val1 val2

# HV Temperature and Voltage

    m_hvVolt = ((valVolt1 << 16) + (valVolt2 << 8) + valVolt3 ) / 1000;
    m_hvTemp = ((valTemp1 << 8) + valTemp2 ) / 10;
    
    cansend vcan0  

# LV Temperature and Voltage

    m_lvVolt = val1;
    m_lvTemp = val3;

    cansend vcan0 0FF#00
    cansend vcan0 0FF#1F

# Inverter Left and Right

    m_invTemp = (((val1 + val2 * 256.0f ) - 15797.0f ) / 112.1182f) * 10.0f;
   
    cansend vcan0 

# Throttle and KW aka Velocity

    m_velocity = (80.0 * currPercMap * m_throttleVal) / 10000.0;

    cansend vcan0 0B0#0100
    cansend vcan0 0B0#0164

# Brake

    m_brakeVal = ( (int) val );

    cansend vcan0 0B0#0200
    cansend vcan0 0B0#0264

# Calibration APPS[0] BSE[1] STEERING[2]
    # steering - sensor - steering - sensor - steering
    # in function, ack, min, max  

    cansend vcan0 0BB#0000 from steering to enter
    cansend vcan0 0BB#0000 as ack ready to set min
    cansend vcan0 0BB#0001 from steering to set max
    cansend vcan0 0BB#0001 as ack to set max 

# FSM from idle to setup run and stop


#!/bin/bash

function CanTest {

    if [ $1 = 'T' ]
    then
        cansend vcan0 0B0#0100
        sleep .1
        cansend vcan0 0B0#010A
        sleep .1
        cansend vcan0 0B0#0114
        sleep .1
        cansend vcan0 0B0#011E
        sleep .1
        cansend vcan0 0B0#0128
        sleep .1
        cansend vcan0 0B0#0132
        sleep .1
        cansend vcan0 0B0#013C
        sleep .1
        cansend vcan0 0B0#0146
        sleep .1
        cansend vcan0 0B0#0150
        sleep .1
        cansend vcan0 0B0#015A
        sleep .1
        cansend vcan0 0B0#0164
    fi

    if [ $1 = 'B' ]
    then
        cansend vcan0 0B0#0200
        sleep .1
        cansend vcan0 0B0#020A
        sleep .1
        cansend vcan0 0B0#0214
        sleep .1
        cansend vcan0 0B0#021E
        sleep .1
        cansend vcan0 0B0#0228
        sleep .1
        cansend vcan0 0B0#0232
        sleep .1
        cansend vcan0 0B0#023C
        sleep .1
        cansend vcan0 0B0#0246
        sleep .1
        cansend vcan0 0B0#0250
        sleep .1
        cansend vcan0 0B0#025A
        sleep .1
        cansend vcan0 0B0#0264
    fi

    if [ $1 = "LV" ]
    then

        cansend vcan0 0FF#00
        sleep .5
        cansend vcan0 0FF#11
        sleep .5
        cansend vcan0 0FF#1F
    fi

    if [ $1 = "HV" ]
    then

        cansend vcan0 0AA#01000000
        sleep .5
        cansend vcan0 0AA#01888888
        sleep .5
        cansend vcan0 0AA#01FFFFFF
        sleep .5
        cansend vcan0 0AA#01
    fi

    if [ $1 = "INV" ]
    then

        cansend vcan0 181#4A0000
        sleep .5
        cansend vcan0 181#4A3949
        sleep .5
        cansend vcan0 181#4AFFFF
        sleep .5
        cansend vcan0 182#4A0000
        sleep .5
        cansend vcan0 182#4A3949
        sleep .5
        cansend vcan0 182#4AFFFF
        sleep .5

    fi

}

CanTest $1








