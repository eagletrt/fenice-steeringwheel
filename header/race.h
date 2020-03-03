#ifndef RACE_H
#define RACE_H
#include <stdint.h>

class Race
{
public:
    Race();
    void setSpeed(int, int);
    void setVelocity(int);
    void setKm(int, int);
    int getSpeed() const;
    int getVelocity() const;
    int getKm() const;
private:
    int speed;
    int velocity;
    int km;
};

#endif // RACE_H
