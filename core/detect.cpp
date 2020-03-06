#include "../header/detect.h"
#include<QDebug>

Detect::Detect(QCanBusDevice* device) {
    this->device = device;
}

void Detect::doWork() {
    qDebug() << "Start Thread";
    connect(device, SIGNAL(framesReceived()),
            this, SLOT(getSerial()));
}

void Detect::getSerial() {
    QByteArray canMsg;
    int canId;

    while(device->framesAvailable()){   
        QCanBusFrame frame = device->readFrame();
        canMsg = frame.payload();
        canId = frame.frameId();
        if(canId != 0){
            emit result(canId, canMsg);
       }
    }
}