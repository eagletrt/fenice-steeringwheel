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

#include "io/buttons.h"

struct priv_t {
  uint8_t *rom;
  uint8_t *cart_ram;
  uint8_t selected_palette[3][4][3];
  uint8_t fb[LCD_HEIGHT][LCD_WIDTH][3];
};

class GameBoy {
public:
  GameBoy();
  ~GameBoy();

  void execute();
  void button_pressed(Buttons::Input button);
  void button_released(Buttons::Input button);
  priv_t *data();

private:
  struct priv_t m_priv;
  void *m_gb;
};

#endif // GAMEBOY_H
