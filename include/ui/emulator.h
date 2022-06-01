#ifndef EMULATOR_H
#define EMULATOR_H

#include "ui/openglwindow.h"

#include <QElapsedTimer>
#include <QOpenGLShaderProgram>

#include "ui/gameboy.h"

class Emulator : public OpenGLWindow {
public:
  using OpenGLWindow::OpenGLWindow;
  Emulator(QWindow *parent = nullptr);
  ~Emulator();

  void initialize() override;
  void render() override;

private:
  GameBoy *m_gb;
  GLuint m_texture = 0;

  QOpenGLShaderProgram *m_program = nullptr;
  QElapsedTimer *m_elapsed;
  int m_frame = 0;
};

#endif // EMULATOR_H
