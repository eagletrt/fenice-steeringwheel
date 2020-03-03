#include "../header/worker.h"

Worker::Worker() {
    test = 1;
}

void Worker::process() {
    qDebug("Hello World!");
    emit finished();
}