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
    cansend vcan0 0FF#88
    sleep .5
    cansend vcan0 0FF#FF
  fi

  if [ $1 = "HV" ]
  then

    cansend vcan0 0AA#010000000000
    sleep .5
    cansend vcan0 0AA#018888888888
    sleep .5
    cansend vcan0 0AA#01FFFFFFFFFF
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
