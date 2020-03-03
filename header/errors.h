#ifndef ERRORS_H
#define ERRORS_H


class Errors
{
public:
    Errors();
    void setErrApps(int);
    void setErrBse(int);
    void setErrSteer(int);
    void setErrLeftWheel(int);
    void setErrRightWheel(int);
    void setErrGps(int);
    void setErrFrontIMU(int);
    void setErrCentralIMU(int);
    void setErrRearIMU(int);
    void setError(int);
    void setAll(int, int, int, int, int, int, int, int, int);
    int getErrApps()const;
    int getErrBse()const;
    int getErrSteer()const;
    int getErrLeftWheel()const;
    int getErrRightWheel()const;
    int getErrGPS()const;
    int getErrFrontIMU()const;
    int getErrCentralIMU()const;
    int getErrRearIMU()const;
    int getError()const;
private:
    int err_apps;
    int err_bse;
    int err_steer;
    int err_wheel_left;
    int err_wheel_right;
    int err_gps;
    int err_imu_front;
    int err_imu_central;
    int err_imu_rear;
    int error;
};

#endif // ERRORS_H
