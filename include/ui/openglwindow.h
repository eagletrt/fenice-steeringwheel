#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLFunctions>
#include <QWindow>

QT_BEGIN_NAMESPACE
class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;
QT_END_NAMESPACE

class OpenGLWindow : public QWindow, protected QOpenGLFunctions {
  Q_OBJECT
public:
  explicit OpenGLWindow(QWindow *parent = nullptr);

  virtual void render();

  virtual void initialize();

  void setAnimating(bool animating);

public slots:
  void renderLater();
  void renderNow();

protected:
  bool event(QEvent *event) override;

  void exposeEvent(QExposeEvent *event) override;

private:
  bool m_animating = false;

  QOpenGLContext *m_context = nullptr;
};

#endif // MAINWINDOW_H
