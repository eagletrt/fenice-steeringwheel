#ifndef TELEMETRY_H
#define TELEMETRY_H

#define NUM_TESTS 5
#define NUM_DRIVERS 5

#include<QDebug>

class Telemetry : public QObject
{
    Q_OBJECT

public:
    Telemetry();
    void setTest(int);
    void setDriver(int);
    void setAsk(bool);
    void setTelemetryStatus(int);
    void setPopupMessage(QChar, QChar, QString);
    void setSender();
    int getTest() const;
    int getDriver() const;
    bool getAsk();
    int getTelemetryStatus() const;
    QString getPopupMessage() const;
    bool getSender() const;
    void getNUM(int*);
private:
    bool test[NUM_TESTS];
    bool driver[NUM_DRIVERS];
    bool ask;
    bool sender;
    int telemetryEnStatus;
    QString popup;
};

#endif // TELEMETRY_H
