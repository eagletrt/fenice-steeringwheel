#ifndef INVERTERS_H
#define INVERTERS_H

#include <QObject>

class Inverters
{
public:
    Inverters();
    void setLeftInverter(int);
    void setRightInverter(int);
    void setPreCharge(int);
    void setLeftInverterTemperature(int, int);
	void setRightInverterTemperature(int, int);
    int getLeftInverter() const;
    int getRightInverter() const;
    int getPreCharge() const;
    int getLeftInverterTemperature() const;
    int getRightInverterTemperature() const;
private:
    int invLeft;
    int invRight;
    int preCharge;
    int invLeftTemp;
    int invRightTemp;
};

#endif // INVERTERS_H
