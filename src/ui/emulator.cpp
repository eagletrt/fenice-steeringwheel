#include "ui/emulator.h"

#include <QQuickWindow>
#include <QRunnable>
#include <QTimer>

Emulator::Emulator() : m_renderer(nullptr) {
  connect(this, &QQuickItem::windowChanged, this, &Emulator::handle_window_changed);
  connect(this, &QQuickItem::visibleChanged, this, &Emulator::handle_visibility_change);
}

void Emulator::handle_window_changed(QQuickWindow *win) {
  if (win) {
    connect(win, &QQuickWindow::beforeSynchronizing, this, &Emulator::sync, Qt::DirectConnection);
    connect(win, &QQuickWindow::sceneGraphInvalidated, this, &Emulator::cleanup, Qt::DirectConnection);
  }
}

void Emulator::handle_visibility_change() { emit visibility_changed(isVisible()); }

void Emulator::cleanup() {
  delete m_renderer;
  m_renderer = nullptr;
}

void Emulator::button_pressed(int button) {
  if (m_renderer) {
    m_renderer->game_boy()->button_pressed((Buttons::Input)button);
  }
}

void Emulator::button_released(int button) {
  if (m_renderer) {
    m_renderer->game_boy()->button_released((Buttons::Input)button);
  }
}

class CleanupJob : public QRunnable {
public:
  CleanupJob(EmulatorRenderer *renderer) : m_renderer(renderer) {}
  void run() override { delete m_renderer; }

private:
  EmulatorRenderer *m_renderer;
};

void Emulator::releaseResources() {
  window()->scheduleRenderJob(new CleanupJob(m_renderer), QQuickWindow::BeforeSynchronizingStage);
  m_renderer = nullptr;
}

EmulatorRenderer::EmulatorRenderer(bool visible) : m_visible(visible) {
  m_gb = new GameBoy();
  m_elapsed = new QElapsedTimer();
}

EmulatorRenderer::~EmulatorRenderer() {
  delete m_gb;
  delete m_elapsed;
  if (m_program) {
    delete m_program;
  }
}

void Emulator::sync() {
  if (!m_renderer) {
    m_renderer = new EmulatorRenderer(isVisible());
    connect(window(), &QQuickWindow::beforeRenderPassRecording, m_renderer, &EmulatorRenderer::init,
            Qt::DirectConnection);
    connect(window(), &QQuickWindow::afterRendering, m_renderer, &EmulatorRenderer::paint, Qt::DirectConnection);
    connect(this, &Emulator::visibility_changed, m_renderer, &EmulatorRenderer::change_visibility);
  }
  m_renderer->set_window_size(window()->size() * window()->devicePixelRatio());
  m_renderer->set_size(size().toSize() * window()->devicePixelRatio());
  m_renderer->set_position(position().toPoint());
  m_renderer->set_window(window());
}

void EmulatorRenderer::change_visibility(bool visible) {
  m_visible = visible;
  if (m_timer) {
    if (visible)
      m_timer->start();
    else
      m_timer->stop();
    m_elapsed->restart();
    m_window->update();
  }
}

void EmulatorRenderer::init() {
  if (!m_program) {
    Q_ASSERT(m_window->rendererInterface()->graphicsApi() == QSGRendererInterface::OpenGL ||
             m_window->rendererInterface()->graphicsApi() == QSGRendererInterface::OpenGLRhi);

    initializeOpenGLFunctions();

    m_program = new QOpenGLShaderProgram();
    m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Vertex, "attribute highp vec2 a_vertices;"
                                                                       "attribute highp vec2 a_texCoords;"
                                                                       "varying highp vec2 texCoords;"
                                                                       "void main() {"
                                                                       "    gl_Position = vec4(a_vertices, 1.0, 1.0);"
                                                                       "    texCoords = a_texCoords;"
                                                                       "}");
    m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment,
                                                "varying highp vec2 texCoords;"
                                                "uniform sampler2D texture0;"
                                                "void main() {"
                                                "    gl_FragColor = texture2D(texture0, texCoords);"
                                                "}");

    m_program->bindAttributeLocation("a_vertices", 0);
    m_program->bindAttributeLocation("a_texCoords", 1);
    m_program->link();

    m_gb->execute();
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB5, LCD_WIDTH, LCD_HEIGHT, 0, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV,
                 (GLvoid *)m_gb->data()->fb);
  }

  if (!m_timer) {
    m_timer = new QTimer();
    m_timer->setInterval(0);
    connect(m_timer, &QTimer::timeout, m_window, &QQuickWindow::update);
    if (m_visible) {
      m_timer->start();
      m_elapsed->start();
    }
  }
}

#define RENDER_SPEED 1

void EmulatorRenderer::paint() {
  if (!m_visible)
    return;

  m_window->beginExternalCommands();

  glViewport(m_position.x(), -m_position.y(), m_size.width(), m_size.height());

  m_program->bind();

  m_program->enableAttributeArray(0);
  m_program->enableAttributeArray(1);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_texture);

  if (m_elapsed->elapsed() >= ((1000. / RENDER_SPEED) / VERTICAL_SYNC)) {
    m_elapsed->restart();
    m_gb->execute();
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, LCD_WIDTH, LCD_HEIGHT, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV,
                    (GLvoid *)m_gb->data()->fb);
  }

  float vertices[] = {
      -1, -1, // top left
      1,  -1, // top right
      -1, 1,  // bottom left
      1,  1   // bottom right
  };

  float texCoords[] = {
      0, 1, 1, 1, 0, 0, 1, 0,
  };

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_texture);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  m_program->setAttributeArray(0, GL_FLOAT, vertices, 2);
  m_program->setAttributeArray(1, GL_FLOAT, texCoords, 2);

  glDisable(GL_DEPTH_TEST);

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  m_program->disableAttributeArray(0);
  m_program->release();

  glViewport(0, 0, m_window_size.width(), m_window_size.height());

  // Not strictly needed for this example, but generally useful for when
  // mixing with raw OpenGL.
  m_window->resetOpenGLState();

  m_window->endExternalCommands();
}
