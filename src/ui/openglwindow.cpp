#include "ui/openglwindow.h"

#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QPainter>

OpenGLWindow::OpenGLWindow(QWindow *parent) : QWindow(parent) { setSurfaceType(QWindow::OpenGLSurface); }

void OpenGLWindow::initialize() {}

void OpenGLWindow::render() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); }

void OpenGLWindow::renderLater() { requestUpdate(); }

bool OpenGLWindow::event(QEvent *event) {
  switch (event->type()) {
  case QEvent::UpdateRequest:
    renderNow();
    return true;
  default:
    return QWindow::event(event);
  }
}

void OpenGLWindow::exposeEvent(QExposeEvent *event) {
  Q_UNUSED(event);

  if (isExposed())
    renderNow();
}

void OpenGLWindow::renderNow() {
  if (!isExposed())
    return;

  bool needsInitialize = false;

  if (!m_context) {
    m_context = new QOpenGLContext(this);
    m_context->setFormat(requestedFormat());
    m_context->create();

    needsInitialize = true;
  }

  m_context->makeCurrent(this);

  if (needsInitialize) {
    initializeOpenGLFunctions();
    initialize();
  }

  render();

  m_context->swapBuffers(this);

  if (m_animating)
    renderLater();
}

void OpenGLWindow::setAnimating(bool animating) {
  m_animating = animating;

  if (animating)
    renderLater();
}
