#include "graphics.h"

Graphics::Graphics(QQuickView *view) { this->view = view; }

void Graphics::startGraphics() {
  qDebug() << "Start Graphics Thread";
  view->show();
}

Graphics::~Graphics() { delete view; }