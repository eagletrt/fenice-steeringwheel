#ifndef INTERFACE_H
#define INTERFACE_H

#include "global.h"
#include <QObject>

class Interface : public QObject {
  Q_OBJECT
public:
  S_PROPERTY(bool, valid, false)

public:
  Interface(QObject *parent = nullptr) : QObject(parent){};
};

#endif // INTERFACE_H
