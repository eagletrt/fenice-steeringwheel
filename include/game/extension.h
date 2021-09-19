#include <QImage>
#include <QMutex>
#include <QThread>
#include <QTimer>
#include <QtQuick/QQuickPaintedItem>

#include "game/gb.h"

class Extension : public QQuickPaintedItem {
  Q_OBJECT
  QML_ELEMENT

public:
  Extension(QQuickItem *parent = 0);
  ~Extension();
  void paint(QPainter *painter);

private:
  QImage *m_image;
  QTimer *m_render_timer;
  QMutex *m_mutex;
  QThread *m_gb_thread;
  GB *m_gb;
};