#ifndef GB_H
#define GB_H

#include <QElapsedTimer>
#include <QObject>
#include <cstdint>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

extern uint16_t &HL;
extern uint16_t PC;
extern uint8_t opcrel;

extern int gameboy[23040];
extern int frame_buffer[23040];
extern uint8_t const key_state[8];

class GB : public QObject {
  Q_OBJECT
public:
  GB(QObject *parent = nullptr);

  enum Input {
    SCANCODE_DOWN,
    SCANCODE_UP,
    SCANCODE_LEFT,
    SCANCODE_RIGHT,
    SCANCODE_TAB,
    SCANCODE_RETURN,
    SCANCODE_Z,
    SCANCODE_X
  };

public slots:
  void render();

signals:
  void framePainted(int *framebuffer);

private:
  void tick();
  uint8_t mem8(uint16_t addr = HL, uint8_t val = 0, int write = 0);
  void set_flags(uint8_t mask, int Z, int N, int H, int C);
  uint16_t read16(uint16_t &addr = PC);
  void push(uint16_t val);
  uint8_t reg8_access(uint8_t val, int write = 1, uint8_t o = opcrel);
  uint8_t get_color(int tile, int y_offset, int x_offset);

private:
  QElapsedTimer m_elapsed;
  bool m_limited;
};

#endif // GB_H