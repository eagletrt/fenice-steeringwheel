#ifndef SENSORS_H
#define SENSORS_H


class Sensors
{
public:
    Sensors();
    void setBrakeVal(int);
    void setThrottleVal(int);
    void setApps(int);
    void setBse(int);
    void setSteer(int);
    void setNumErrApps(int);
    void setNumErrBse(int);
    void setNumErrSteer(int);
    int getBrakeVal()const;
    int getThrottleVal()const;
    int getApps()const;
    int getBse()const;
    int getSteer()const;
    int getNumErrApps()const;
    int getNumErrBse()const;
    int getNumErrSteer()const;
private:
    int brakeVal;
    int throttleVal;
    int apps;
    int bse;
    int steer;
    int num_err_apps;
    int num_err_bse;
    int num_err_steer;
};

#endif // SENSORS_H
