#include "../header/lv.h"

Lv::Lv() {
    this->lvTemp = 0;
    this->lvVolt = 0;
}
void Lv::setLvTemp(int val) {
    lvTemp = val;
}
void Lv::setLvVolt(int val) {
    lvVolt = val;
}
int Lv::getLvTemp() const {
    return lvTemp;
}
int Lv::getLvVolt() const {
    return lvVolt;
}