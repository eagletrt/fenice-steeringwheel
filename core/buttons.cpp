#include "../header/buttons.h"
#include <QDebug>

/*

This class is used to handle events from rpi gpio

Encoder 1-2-3

100  1        106  1        108   1
101  2        107  2        109   2
102  3        115  3        110   3
103  4        113  4        111   4  
104  5        114  5        112   5
105  6        112  6        113   6

Buttons:

paddle top L/R  108/109
paddle bottom L/R  

bottom left/right 110/111

*/

Buttons::Buttons(QGuiApplication *app){

    // Init GPIO access
    wiringPiSetup();
    mcp23017Setup (100, 0x20) ;
    // Create a timer
    timer = new QTimer(this);

    pinMap = QVector<int>();
    pinState = QVector<int>();
    previusPinState = QVector<int>();
    buttonState = QVector<States>();

    buttonAction = -1;
    oldTc = -1;
    oldPump = -1;
    oldMap = -1;
    tc = -1;
    pump = -1;
    map = -1;

    switchTimer = QTime();
    switchTimer.start();

    switchIsWrong = false;

    pinEnabled = {2,3,4,5,7,21,23,25,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115};

    for (int i=0; i < pinEnabled.size(); i++) {
        pinMode(pinEnabled[i], INPUT);
        pullUpDnControl(pinEnabled[i], PUD_UP);

        pinState.append(1);
        previusPinState.append(1);
        buttonState.append(BUTTON_NORMAL);
    }

    // Setup signal/slot mechanism
    connect(timer, SIGNAL(timeout()),this, SLOT(readGPIOState()));

    // Start timer
    timer->start(30);
}

void Buttons::readGPIOState(){
  
    for (int i=0; i < pinEnabled.size(); i++) {
        pinState[i] = digitalRead(pinEnabled.at(i));

        if (pinState.at(i) != previusPinState.at(i)) {

            buttonAction = -1;
            pump = -1;
            map = -1;
            tc = -1;

            // qDebug() << "####### PIN " << pinEnabled[i] << "is " << pinState[i] << " #######";

            changeButtonState(i);

            emitButton(pinEnabled[i]);

            changeManettino(pinEnabled[i]);
            
            if ((map != -1 && map != oldMap) || (pump != -1 && pump != oldPump) || (tc != -1 && tc != oldTc)) {
                
                int timeElapsed = switchTimer.restart();

                if (timeElapsed < 15) {
                    switchIsWrong = true;
                }

                if (!switchIsWrong) {
                    if(map != -1 && map != oldMap){
                        mapChanged(map);
                        oldMap = map;
                    }
                    if(pump != -1 && pump != oldPump){
                        pumpChanged(pump);
                        oldPump = pump;
                    }
                    if(tc != -1 && tc != oldTc){
                        tcChanged(tc);
                        oldTc = tc;
                    }
                }

                switchIsWrong = false;
            }
        }

      previusPinState[i] = pinState.at(i);
    }
}
    
void Buttons::changeManettino(int gpio){
    // Change TC, Pump, Maps
    switch(gpio) {
        case PUMP_1:
            this->pump = 1;
        break;
        case PUMP_2:
            this->pump = 2;
        break;
        case PUMP_3:
            this->pump = 3;
        break;
        case PUMP_4:
            this->pump = 4;
        break;
        case PUMP_5:
            this->pump = 5;
        break;
        case PUMP_6:
            this->pump = 6;
        break;
        case MAP_1:
            this->map = 1;
        break;
        case MAP_2:
            this->map = 2;
        break;
        case MAP_3:
            this->map = 3;
        break;
        case MAP_4:
            this->map = 4;
        break;
        case MAP_5:
            this->map = 5;
        break;
        case MAP_6:
            this->map = 6;
        break;
        case TC_OFF:
            this->tc = 0;
        break;
        case TC_1:
            this->tc = 1;
        break;
        case TC_2:
            this->tc = 2;
        break;
        case TC_3:
            this->tc = 3;
        break;
        case TC_4:
            this->tc = 4;
        break;
        case TC_AUTO:
            this->tc = 4;
        break;
    }
}

void Buttons::changeButtonState(int index){
    // Set Button State
    switch (buttonState.at(index)) {
        case BUTTON_NORMAL:
            this->buttonState[index] = BUTTON_PRESSED;
            this->buttonAction = BUTTON_PRESSED;
        break;
        case BUTTON_PRESSED:
            this->buttonState[index] = BUTTON_NORMAL;
            this->buttonAction = BUTTON_NORMAL;
        break;
    }
}

void Buttons::emitButton(int gpio){
    // Emit btn 
    switch (gpio) {
        case BUTTON_TOP_LEFT:
            emitButtonEvent(0, this->buttonAction);
        break;
        case BUTTON_BOTTOM_LEFT:
            emitButtonEvent(1, this->buttonAction);
        break;
        case BUTTON_BOTTOM_RIGHT:
            emitButtonEvent(2, this->buttonAction);
        break;
        case BUTTON_TOP_RIGHT:
            emitButtonEvent(3, this->buttonAction);
        break;
        case PADDLE_LEFT:
            emitButtonEvent(4, this->buttonAction);
        break;
        case PADDLE_RIGHT:
            emitButtonEvent(5, this->buttonAction);
        break;
    }
}

void Buttons::emitButtonEvent(int buttonId, int buttonAction) {
    // Emit btn events
    if (buttonAction == BUTTON_PRESSED) {
        emit btnPressed(buttonId);
    } else {
       emit btnReleased(buttonId);
       emit btnClicked(buttonId);
    }
}