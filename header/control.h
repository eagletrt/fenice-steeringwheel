#ifndef CONTROL_H
#define CONTROL_H


class Control
{
public:
    Control();
    void setCtrlIsEnabled(bool);
    void setCtrlIsOn(bool);
    bool setCarStatus(int);
    bool getCtrlIsEnabled() const;
    bool getCtrlIsOn() const;
    int getCarStatus() const;
private:
    bool ctrlIsEnabled;
    bool ctrlIsOn;
    int carStatus;
};

#endif // CONTROL_H
