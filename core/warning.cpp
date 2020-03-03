#include "../header/warning.h"

Warning::Warning()
{
    this->invRight = 2;
    this->invLeft = 2;
    this->front = 2;
    this->central = 2;
    this->pedals = 2;
    this->rear = 2;
    this->lv = 2;
    this->hv = 2;
}

void Warning::setInvRight(int value){
    this->invRight = value;
}

void Warning::setInvLeft(int value){
    this->invLeft = value;
}

void Warning::setFront(int value){
    this->front = value;
}

void Warning::setCentral(int value){
    this->central = value;
}

void Warning::setRear(int value){
    this->rear = value;
}

void Warning::setPedals(int value){
    this->pedals = value;
}

void Warning::setLv(int value){
    this->lv = value;
}

void Warning::setHv(int value){
    this->hv = value;
}

void Warning::setWarning(int value){
    this->warning = value;
}

int Warning::getInvRight() const{
    return this->invRight;
}

int Warning::getInvLeft() const{
    return this->invLeft;
}

int Warning::getFront() const{
    return this->front;
}

int Warning::getCentral() const{
    return this->central;
}

int Warning::getRear() const{
    return this->rear;
}

int Warning::getPedals() const{
    return this->pedals;
}

int Warning::getLv() const{
    return this->lv;
}

int Warning::getHv() const{
    return this->hv;
}

int Warning::getWarning() const{
    return this->warning;
}