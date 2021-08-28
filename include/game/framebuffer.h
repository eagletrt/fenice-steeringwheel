#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#define GL_GLEXT_PROTOTYPES
#include <QOpenGLBuffer>
#include <QOpenGLDebugLogger>
#include <QOpenGLFramebufferObjectFormat>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QQuickFramebufferObject>
#include <QTimer>

class FramebufferItem;

class FramebufferRenderer : public QQuickFramebufferObject::Renderer {
private:
  const FramebufferItem *m_item;
  QOpenGLDebugLogger *m_logger;
  QOpenGLShaderProgram *m_program;
  QOpenGLVertexArrayObject *m_vao;
  QOpenGLBuffer *m_vbo, *m_ebo;
  QOpenGLTexture *m_texture;
  QTimer *m_render_timer;

public:
  FramebufferRenderer(const FramebufferItem *item);
  ~FramebufferRenderer();
  QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) {
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    // optionally enable multisampling by doing format.setSamples(4);
    return new QOpenGLFramebufferObject(size, format);
  }
  void render();
};

class FramebufferItem : public QQuickFramebufferObject {
  QQuickFramebufferObject::Renderer *createRenderer() const { return new FramebufferRenderer(this); }
};

#endif // FRAMEBUFFER_H
