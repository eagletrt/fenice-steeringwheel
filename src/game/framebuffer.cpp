#include "game/framebuffer.h"

#include <QQuickWindow>
#include <QSGRendererInterface>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480

#define GB_WIDTH 160
#define GB_HEIGHT 144

#define FB_WIDTH GB_WIDTH * 3
#define FB_HEIGHT GB_HEIGHT * 3

#define FB_NORMALIZED_WIDTH (float)FB_WIDTH / (float)SCREEN_WIDTH
#define FB_NORMALIZED_HEIGHT (float)FB_HEIGHT / (float)SCREEN_HEIGHT

QVector<QVector2D> m_vertices = {
    // positions
    QVector2D(FB_NORMALIZED_WIDTH, FB_NORMALIZED_HEIGHT),   // top right
    QVector2D(FB_NORMALIZED_WIDTH, -FB_NORMALIZED_HEIGHT),  // bottom right
    QVector2D(-FB_NORMALIZED_WIDTH, -FB_NORMALIZED_HEIGHT), // bottom left
    QVector2D(-FB_NORMALIZED_WIDTH, FB_NORMALIZED_HEIGHT),  // top left
};

QVector<QVector2D> m_tex_coords = {QVector2D(1.0f, 1.0f), QVector2D(1.0f, 0.0f), QVector2D(0.0f, 0.0f),
                                   QVector2D(0.0f, 1.0f)};

QVector<GLuint> m_indices = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

FramebufferRenderer::FramebufferRenderer(const FramebufferItem *item) : m_item(item) {
  QSGRendererInterface *rif = m_item->window()->rendererInterface();
  Q_ASSERT(rif->graphicsApi() == QSGRendererInterface::OpenGL || rif->graphicsApi() == QSGRendererInterface::OpenGLRhi);

  m_logger = new QOpenGLDebugLogger();
  m_logger->initialize(); // initializes in the current context, i.e. ctx

  QObject::connect(m_logger, &QOpenGLDebugLogger::messageLogged, m_logger,
                   [&](const QOpenGLDebugMessage &debugMessage) {
                     if (debugMessage.type() == QOpenGLDebugMessage::ErrorType)
                       qDebug() << debugMessage;
                   });
  m_logger->startLogging();

  m_program = new QOpenGLShaderProgram();
  m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Vertex,
                                              R"(
attribute vec2 vertex;
attribute vec2 textureCoordinate;

varying vec2 varyingTextureCoordinate;

void main() {
  gl_Position = vec4(vertex, 1.0, 1.0);
  varyingTextureCoordinate = vec2(textureCoordinate.x, textureCoordinate.y);
})");
  m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment,
                                              R"(
varying vec2 varyingTextureCoordinate;

uniform sampler2D texture;

void main() {
	gl_FragColor = texture2D(texture, varyingTextureCoordinate);
}
)");

  m_program->link();

  m_texture = new QOpenGLTexture(QOpenGLTexture::Target2D);

  m_texture->setMinificationFilter(QOpenGLTexture::Filter::Nearest);
  m_texture->setMagnificationFilter(QOpenGLTexture::Filter::Nearest);
  m_texture->create();

  m_texture->setSize(GB_WIDTH, GB_HEIGHT, 1);
  m_texture->setWrapMode(QOpenGLTexture::WrapMode::Repeat);
  m_texture->setFormat(QOpenGLTexture::TextureFormat::RGBA8_UNorm);
  m_texture->allocateStorage();

  int32_t data[GB_WIDTH * GB_HEIGHT];
  for (int32_t i = 0; i < GB_WIDTH * GB_HEIGHT; i++) {
    data[i] = 0xFFFFFFFF;
  }

  m_texture->setData(QOpenGLTexture::PixelFormat::RGBA, QOpenGLTexture::PixelType::UInt32_RGBA8_Rev,
                     (const void *)data);

  m_texture->generateMipMaps();

  m_gb = new GB();
  m_gb_thread = new QThread();
  m_gb->moveToThread(m_gb_thread);
  QObject::connect(m_gb_thread, &QThread::started, m_gb, &GB::render);
  QObject::connect(m_gb, &GB::framePainted, m_gb_thread, [&](int *framebuffer) {
    int copy[23040];
    memcpy(copy, framebuffer, 23040 * sizeof(int));
    m_texture->setData(QOpenGLTexture::PixelFormat::RGBA, QOpenGLTexture::PixelType::UInt32_RGBA8_Rev,
                       (const void *)copy);
    m_texture->generateMipMaps();
  });
  m_gb_thread->start();

  m_render_timer = new QTimer();
  QObject::connect(m_render_timer, &QTimer::timeout, m_render_timer, [&]() { update(); });
  m_render_timer->start(1. / 0.03);
}

FramebufferRenderer::~FramebufferRenderer() {
  m_gb_thread->quit();
  m_gb_thread->wait();

  delete m_gb_thread;
  delete m_gb;
  delete m_logger;
  delete m_render_timer;
}

void FramebufferRenderer::render() {
  m_item->window()->beginExternalCommands();

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  m_program->bind();
  m_program->setUniformValue("texture", 0);

  glActiveTexture(GL_TEXTURE0);
  m_texture->bind();

  m_program->setAttributeArray("vertex", m_vertices.constData());
  m_program->enableAttributeArray("vertex");

  m_program->setAttributeArray("textureCoordinate", m_tex_coords.constData());
  m_program->enableAttributeArray("textureCoordinate");

  glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());

  m_program->release();

  m_item->window()->resetOpenGLState();
  m_item->window()->endExternalCommands();
}
