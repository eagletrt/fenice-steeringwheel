#ifndef PTT_H
#define PTT_H

#include <QObject>

class Ptt : public QObject {
  Q_OBJECT
public:
  explicit Ptt(QObject *parent = nullptr);

  void start();
  void stop();
};

#endif // PTT_H
