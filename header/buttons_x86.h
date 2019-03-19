#ifndef BUTTONS_X86_H
#define BUTTONS_X86_H

#include <QVector>
#include <QGuiApplication>

#include "keypresseventfilter.h"

class Buttons : public QObject
{
    Q_OBJECT
    public:
        Buttons(QGuiApplication *app);

    signals:
        void btnClicked(int btnID);
        void btnPressed(int btnID);
        void btnReleased(int btnID);
        void presetChanged(int presetID);
        void pumpChanged(int pumpID);

    public slots:
        void handleKeyboardPress(int btnID);

    private:
        KeyPressEventFilter *filter;

        enum Constants {
            BTN_NORMAL = 0,
            BTN_PRESSED = 1,
        };

        int counter;
        QVector<int> pinMap;
        QVector<int> pinState;
        QVector<int> btnState;
        QVector<int> previusPinState;
};

#endif // BUTTONS_X86_H
