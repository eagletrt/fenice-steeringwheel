#ifndef EMULATOR_H
#define EMULATOR_H

#include <QOpenGLFunctions>
#include <QQuickItem>

#include <QElapsedTimer>
#include <QOpenGLShaderProgram>

#include "ui/gameboy.h"

class EmulatorRenderer : public QObject, protected QOpenGLFunctions {
  Q_OBJECT
public:
  EmulatorRenderer(bool visible = true);
  ~EmulatorRenderer();

  void set_window_size(const QSize &size) { m_window_size = size; }
  void set_size(const QSize &size) { m_size = size; }
  void set_position(const QPoint &position) { m_position = position; }
  void set_window(QQuickWindow *window) { m_window = window; }

  GameBoy *game_boy() { return m_gb; }

public slots:
  void init();
  void paint();
  void change_visibility(bool visible);

private:
  bool m_visible = true;

  GameBoy *m_gb = nullptr;
  QElapsedTimer *m_elapsed = nullptr;
  QTimer *m_timer = nullptr;

  QOpenGLShaderProgram *m_program = nullptr;
  GLuint m_texture = 0;

  QSize m_window_size;
  QSize m_size;
  QPoint m_position;

  QQuickWindow *m_window = nullptr;
};

class Emulator : public QQuickItem {
  Q_OBJECT
  QML_ELEMENT

public:
  Emulator();

public slots:
  void sync();
  void cleanup();
  void button_pressed(int button);
  void button_released(int button);

signals:
  void visibility_changed(bool visible);

private slots:
  void handle_window_changed(QQuickWindow *win);
  void handle_visibility_change();

private:
  void releaseResources() override;
  qreal m_t;
  EmulatorRenderer *m_renderer;
};

#endif // EMULATOR_H
