#include "ui/emulator.h"

#include <QScreen>

Emulator::Emulator(QWindow *parent) : OpenGLWindow(parent) {
  m_elapsed = new QElapsedTimer();
  m_gb = new GameBoy();
}

Emulator::~Emulator() {
  delete m_elapsed;
  delete m_gb;
  if (m_program) {
    delete m_program;
  }
}

void Emulator::initialize() {
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

  setAnimating(true);
}

void Emulator::render() {
  if (m_elapsed->isValid() && m_elapsed->elapsed() < (1000. / VERTICAL_SYNC))
    return;
  m_elapsed->restart();
  m_gb->execute();

  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, LCD_WIDTH, LCD_HEIGHT, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV,
                  (GLvoid *)m_gb->data()->fb);

  glViewport((width() - height() * 1.1) / 2, 0, height() * 1.1, height());

  m_program->bind();

  m_program->enableAttributeArray(0);
  m_program->enableAttributeArray(1);

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

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  m_program->disableAttributeArray(0);
  m_program->release();
}
