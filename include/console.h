#ifndef CONSOLE_H
#define CONSOLE_H
#include <QObject>

class Console : public QObject {
  Q_OBJECT

public:
  Console();

public slots:
  void onClicked(int btnID);
  void onPressed(int btnID);
  void onReleased(int btnID);
};

#endif // CONSOLE_H
