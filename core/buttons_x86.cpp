#include "../header/buttons_x86.h"
#include <QDebug>

Buttons::Buttons(QGuiApplication *app)
{

    filter = new KeyPressEventFilter(app);

    QObject::connect(filter, &KeyPressEventFilter::keyboardBtnClicked,
                     this, &Buttons::handleKeyboardPress);

    pinMap = QVector<int>();
    pinState = QVector<int>();
    previusPinState = QVector<int>();
    btnState = QVector<int>();

    pinMap << 12 << 14 << 26;
    pinState << 1 << 1 << 1;
    previusPinState << 1 << 1 << 1;

    btnState << BTN_NORMAL << BTN_NORMAL << BTN_NORMAL;
}

//  KeyBoard Map 
//  q:  exit,run/stop    (0) 
//  a:  send,start       (1)
//  d:  enter, down      (2)
//  r:  marker,telemetry (3)
//  z:  paddle_btm_left  (4)
//  x:  paddle_btm_right (5)
//  c:  paddle_top_left  (6)
//  v:  paddle_top_right (7)
//  s:  button_start     (8)
//  1-6:Map X            (11-16)     

void Buttons::handleKeyboardPress(int btnID) {
    //Encoder or Buttons
    if (btnID < 10) {
        emit btnClicked(btnID);
    } else if(btnID > 10 && btnID < 20){
        emit tcChanged(btnID -10);   
    } else if(btnID > 20 && btnID < 30){
        emit pumpChanged(btnID -20); 
    } else if (btnID > 30) {
        emit mapChanged(btnID - 30);
    }
}
