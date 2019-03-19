#ifndef BUTTONS_H
#define BUTTONS_H

#include <QTimer>
#include <QVector>
#include <QGuiApplication>
#include <QTime>

#include "lib/mcp23017.h"
#include "lib/wiringPi.h"

class Buttons : public QObject
{
    Q_OBJECT
    public:
        Buttons(QGuiApplication *app);
        QTimer *timer;

    public slots:
        void readGPIOState();

    signals:
        void btnClicked(int btnID);
        void btnPressed(int btnID);
        void btnReleased(int btnID);
        void presetChanged(int presetID);
        void pumpChanged(int pumpID);

    private:
        enum Constants {
            BTN_NORMAL = 0,
            BTN_PRESSED = 1,
        };

        int btnAction;
        int map;
        int oldMap;
        int pump;
        int oldPump;

        bool isBackFromMap6;
        bool isBackFromMap3;
        bool switchIsWrong;

        QTime switchTimer;

        QVector<int> pinMap;
        QVector<int> pinState;
        QVector<int> btnState;
        QVector<int> previusPinState;

        QVector<int> pinEnabled;

        void emitBtnEvent(int btnId, int btnAction);
};

#endif // BUTTONS_H
