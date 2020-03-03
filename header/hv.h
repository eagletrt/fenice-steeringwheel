#ifndef HV_H
#define HV_H


class Hv
{
public:
    Hv();
    void setHvTemp(int, int);
    void setHvVolt(int, int , int);
    int getHvTemp() const;
    int getHvVolt() const;
private:
    int hvTemp;
    int hvVolt;
};

#endif // HV_H
