#include "game/extension.h"

#include <QPainter>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480

#define GB_WIDTH 160
#define GB_HEIGHT 144

#define FB_WIDTH GB_WIDTH * 3
#define FB_HEIGHT GB_HEIGHT * 3

#define FB_X (SCREEN_WIDTH - FB_WIDTH) / 2
#define FB_Y (SCREEN_HEIGHT - FB_HEIGHT) / 2

Extension::Extension(QQuickItem *parent) : QQuickPaintedItem(parent) {
  m_gb = new GB();
  m_gb_thread = new QThread(this);
  m_gb->moveToThread(m_gb_thread);
  m_mutex = new QMutex();

  QObject::connect(m_gb_thread, &QThread::started, m_gb, &GB::render);

  m_gb_thread->start();

  m_image = new QImage((uchar*)frame_buffer, GB_WIDTH, GB_HEIGHT, QImage::Format::Format_RGBX8888);
}

Extension::~Extension() {
  m_gb_thread->quit();
  m_gb_thread->wait();

  delete m_gb_thread;
  delete m_gb;
}

void Extension::paint(QPainter *painter) {
  painter->drawImage(QRect(FB_X, FB_Y, FB_WIDTH, FB_HEIGHT), *m_image);
  update();
}