#ifndef DETECT_H
#define DETECT_H

#include <QThread>
#include <QString>
#include <QCanBus>
#include <QByteArray>

class Detect : public QObject {
    Q_OBJECT
    QCanBusDevice* device;
public slots:
    void doWork();
    void getSerial();
signals:
    void result(int canId, QByteArray canMsg);
public:
    Detect(QCanBusDevice*);
};

#endif // DETECT_H
