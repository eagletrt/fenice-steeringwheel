#ifndef GAMEBOY_H
#define GAMEBOY_H

#define LCD_HEIGHT 144
#define LCD_WIDTH 160

#define DMG_CLOCK_FREQ 4194304.0
#define SCREEN_REFRESH_CYCLES 70224.0
#define VERTICAL_SYNC (DMG_CLOCK_FREQ / SCREEN_REFRESH_CYCLES)

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct priv_t {
  uint8_t *rom;
  uint8_t *cart_ram;
  uint16_t selected_palette[3][4];
  uint16_t fb[LCD_HEIGHT][LCD_WIDTH];
};

class GameBoy {
public:
  GameBoy();

  void execute();
  priv_t *data();

private:
  struct priv_t m_priv;
  void *m_gb;
};

#endif // GAMEBOY_H
