#ifndef WARNING_H
#define WARNING_H

class Warning
{
public:
    Warning();
    void setInvRight(int);
    void setInvLeft(int);
    void setFront(int);
    void setRear(int);
    void setLv(int);
    void setHv(int);
    void setCentral(int);
    void setPedals(int);
    void setWarning(int);
    int getInvRight() const;
    int getInvLeft() const;
    int getFront() const;
    int getRear() const;
    int getLv() const;
    int getHv() const;
    int getCentral() const;
    int getPedals() const;
    int getWarning() const;
private:
    int invRight;
    int invLeft;
    int front;
    int rear;
    int lv;
    int hv;
    int central;
    int pedals;
    int warning;
};

#endif // WARNING_H
