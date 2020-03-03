#ifndef BUTTONS_H
#define BUTTONS_H

#include <QTimer>
#include <QVector>
#include <QGuiApplication>
#include <QTime>

#include "lib/mcp23017.h"
#include "lib/wiringPi.h"

#define BUTTON_TOP_LEFT       110
#define BUTTON_TOP_RIGHT      108
#define BUTTON_BOTTOM_LEFT    111
#define BUTTON_BOTTOM_RIGHT   25

#define PADDLE_LEFT           109
#define PADDLE_RIGHT          23

#define MAP_1              7
#define MAP_2              2
#define MAP_3              3
#define MAP_4              4
#define MAP_5              5
#define MAP_6              21

#define PUMP_1             106
#define PUMP_2             107
#define PUMP_3             115
#define PUMP_4             113
#define PUMP_5             114
#define PUMP_6             112

#define TC_OFF             100
#define TC_1               101
#define TC_2               102
#define TC_3               103
#define TC_4               104
#define TC_AUTO            105

// Fenice To Do:

#define BUTTON_CENTER      11110029     

#define PADDLE_BTM_LEFT    109
#define PADDLE_BTM_RIGHT   23
#define PADDLE_TOP_LEFT    11110912
#define PADDLE_TOP_RIGHT   11110090

class Buttons : public QObject
{
    Q_OBJECT
    public:
        Buttons(QGuiApplication *app);
        QTimer *timer;
        enum States {
            BUTTON_NORMAL = 0,
            BUTTON_PRESSED = 1,
        };

        int buttonAction;
        int map;
        int oldMap;
        int pump;
        int oldPump;
        int tc;
        int oldTc;

    public slots:
        void readGPIOState();
        void changeManettino(int gpio);
        void changeButtonState(int index);
        void emitButton(int gpio);
        void emitButtonEvent(int buttonId, int buttonAction);

    signals:
        void btnClicked(int btnID);
        void btnPressed(int btnID);
        void btnReleased(int btnID);
        void mapChanged(int mapID);
        void pumpChanged(int pumpID);
        void tcChanged(int tcID);

    private:

        bool switchIsWrong;

        QTime switchTimer;

        QVector<int> pinMap;
        QVector<int> pinState;
        QVector<States> buttonState;
        QVector<int> previusPinState;

        QVector<int> pinEnabled;
};

#endif // BUTTONS_H
