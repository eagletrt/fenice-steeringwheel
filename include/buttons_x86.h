#ifndef BUTTONS_X86_H
#define BUTTONS_X86_H

#include <QGuiApplication>
#include <QVector>

#include "keypresseventfilter.h"

class Buttons : public QObject {
  Q_OBJECT
public:
  Buttons(QGuiApplication *app, QObject *parent = nullptr);
  ~Buttons();

signals:
  void buttonClicked(int btnID);
  void buttonPressed(int btnID);
  void buttonReleased(int btnID);
  void mapChanged(int mapID);
  void pumpChanged(int pumpID);
  void tractionControlChanged(int tcID);

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
