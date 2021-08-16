#ifndef LV_H
#define LV_H

#include <QObject>

class LV : public QObject {
  Q_OBJECT
public:
  LV(QObject *parent = nullptr);
  ~LV();

private:
};

#endif // LV_H
