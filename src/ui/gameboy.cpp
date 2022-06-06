#include "ui/gameboy.h"

#include "global.h"
#include <QFile>

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern "C" {
#include "ui/peanut.h"
}

/**
 * Returns a byte from the ROM file at the given address.
 */
uint8_t gb_rom_read(gb_s *gb, const uint_fast32_t addr) {
  const priv_t *const p = (const priv_t *const)gb->direct.priv;
  return p->rom[addr];
}

/**
 * Returns a byte from the cartridge RAM at the given address.
 */
uint8_t gb_cart_ram_read(gb_s *gb, const uint_fast32_t addr) {
  const priv_t *const p = (const priv_t *const)gb->direct.priv;
  return p->cart_ram[addr];
}

/**
 * Writes a given byte to the cartridge RAM at the given address.
 */
void gb_cart_ram_write(gb_s *gb, const uint_fast32_t addr, const uint8_t val) {
  const priv_t *const p = (const priv_t *const)gb->direct.priv;
  p->cart_ram[addr] = val;
}

void auto_assign_palette(priv_t *priv, uint8_t game_checksum) {
  size_t palette_bytes = 3 * 4 * 3 * sizeof(uint8_t);

  switch (game_checksum) {
  /* Pokemon Blue */
  case 0x61:
  case 0x45:

  /* Pokemon Blue Star */
  case 0xD8: {
    const uint8_t palette[3][4][3] = {{{255, 255, 255}, {255, 132, 132}, {148, 58, 58}, {0, 0, 0}},
                                      {{255, 255, 255}, {99, 165, 255}, {0, 0, 255}, {0, 0, 0}},
                                      {{255, 255, 255}, {99, 165, 255}, {0, 0, 255}, {0, 0, 0}}};
    memcpy(priv->selected_palette, palette, palette_bytes);
    break;
  }

  default: {
    const uint8_t palette[3][4][3] = {{{255, 255, 255}, {120, 120, 120}, {60, 60, 60}, {0, 0, 0}},
                                      {{255, 255, 255}, {120, 120, 120}, {60, 60, 60}, {0, 0, 0}},
                                      {{255, 255, 255}, {120, 120, 120}, {60, 60, 60}, {0, 0, 0}}};
    sDebug("gameboy") << "no palette found for game with checksum" << Qt::hex << game_checksum;
    memcpy(priv->selected_palette, palette, palette_bytes);
  }
  }
}

void lcd_draw_line(gb_s *gb, const uint8_t pixels[160], const uint_least8_t line) {
  priv_t *priv = (priv_t *)gb->direct.priv;

  for (unsigned int x = 0; x < LCD_WIDTH; x++) {
    priv->fb[line][x][0] = priv->selected_palette[(pixels[x] & LCD_PALETTE_ALL) >> 4][pixels[x] & 3][0];
    priv->fb[line][x][1] = priv->selected_palette[(pixels[x] & LCD_PALETTE_ALL) >> 4][pixels[x] & 3][1];
    priv->fb[line][x][2] = priv->selected_palette[(pixels[x] & LCD_PALETTE_ALL) >> 4][pixels[x] & 3][2];
  }
}

/**
 * Handles an error reported by the emulator. The emulator context may be used
 * to better understand why the error given in gb_err was reported.
 */
void gb_error(gb_s *gb, const enum gb_error_e gb_err, const uint16_t val) {
  switch (gb_err) {
  case GB_INVALID_OPCODE:
    /* We compensate for the post-increment in the __gb_step_cpu
     * function. */
    sCritical("gameboy") << "invalid opcode" << Qt::hex << val << "at PC:" << Qt::hex << gb->cpu_reg.pc - 1
                         << "SP:" << Qt::hex << gb->cpu_reg.sp;
    break;

  /* Ignoring non fatal errors. */
  case GB_INVALID_WRITE:
    sWarning("gameboy") << "invalid write" << Qt::hex << val << "at PC:" << Qt::hex << gb->cpu_reg.pc - 1
                        << "SP:" << Qt::hex << gb->cpu_reg.sp;
    return;

  case GB_INVALID_READ:
    sWarning("gameboy") << "invalid read" << Qt::hex << val << "at PC:" << Qt::hex << gb->cpu_reg.pc - 1
                        << "SP:" << Qt::hex << gb->cpu_reg.sp;
    return;

  default:
    sCritical("gameboy") << "unknown error";
    break;
  }
}

GameBoy::GameBoy() : m_gb() {
  m_priv = {.rom = NULL, .cart_ram = NULL, .selected_palette = {}, .fb = {}};

  QFile romFile(":/rom.gb");
  if (!romFile.open(QIODevice::ReadOnly))
    return;

  QByteArray blob = romFile.readAll();

  m_priv.rom = (uint8_t *)malloc(blob.size());
  memcpy(m_priv.rom, blob.data(), blob.size());

  romFile.close();

  m_gb = malloc(sizeof(gb_s));

  gb_init((gb_s *)m_gb, &gb_rom_read, &gb_cart_ram_read, &gb_cart_ram_write, &gb_error, &m_priv);

  gb_init_lcd((gb_s *)m_gb, &lcd_draw_line);

  auto_assign_palette(&m_priv, gb_colour_hash((gb_s *)m_gb));

  uint_fast32_t ram_size = gb_get_save_size((gb_s *)m_gb);

  QFile ramFile("./ram.save");
  if (ramFile.open(QIODevice::ReadOnly)) {
    QByteArray blob = ramFile.read(ram_size);
    m_priv.cart_ram = (uint8_t *)malloc(ram_size);
    memcpy(m_priv.cart_ram, blob.data(), ram_size);
    ramFile.close();
  } else {
    m_priv.cart_ram = (uint8_t *)malloc(ram_size);
  }
}

GameBoy::~GameBoy() {
  uint_fast32_t ram_size = gb_get_save_size((gb_s *)m_gb);
  QFile file("./ram.save");
  if (file.open(QIODevice::WriteOnly)) {
    file.write((const char *)m_priv.cart_ram, (int)ram_size);
    file.close();
  } else {
  }

  delete m_priv.rom;
  delete m_priv.cart_ram;
  gb_s *gb = (gb_s *)m_gb;
  delete gb;
}

void GameBoy::execute() { gb_run_frame((gb_s *)m_gb); }

void GameBoy::button_pressed(Buttons::Input button) {
  gb_s *gb = (gb_s *)m_gb;
  switch (button) {
  case Buttons::Input::BUTTON_BOTTOM_LEFT:
    gb->direct.joypad_bits.up = 0;
    break;
  case Buttons::Input::BUTTON_TOP_LEFT:
    gb->direct.joypad_bits.left = 0;
    break;
  case Buttons::Input::BUTTON_BOTTOM_RIGHT:
    gb->direct.joypad_bits.down = 0;
    break;
  case Buttons::Input::BUTTON_TOP_RIGHT:
    gb->direct.joypad_bits.right = 0;
    break;
  case Buttons::Input::PADDLE_TOP_LEFT:
    gb->direct.joypad_bits.b = 0;
    break;
  case Buttons::Input::PADDLE_TOP_RIGHT:
    gb->direct.joypad_bits.a = 0;
    break;
  case Buttons::Input::BUTTON_START_STOP:
    gb->direct.joypad_bits.start = 0;
    break;
  default:
    break;
  }
}

void GameBoy::button_released(Buttons::Input button) {
  gb_s *gb = (gb_s *)m_gb;
  switch (button) {
  case Buttons::Input::BUTTON_BOTTOM_LEFT:
    gb->direct.joypad_bits.up = 1;
    break;
  case Buttons::Input::BUTTON_TOP_LEFT:
    gb->direct.joypad_bits.left = 1;
    break;
  case Buttons::Input::BUTTON_BOTTOM_RIGHT:
    gb->direct.joypad_bits.down = 1;
    break;
  case Buttons::Input::BUTTON_TOP_RIGHT:
    gb->direct.joypad_bits.right = 1;
    break;
  case Buttons::Input::PADDLE_TOP_LEFT:
    gb->direct.joypad_bits.b = 1;
    break;
  case Buttons::Input::PADDLE_TOP_RIGHT:
    gb->direct.joypad_bits.a = 1;
    break;
  case Buttons::Input::BUTTON_START_STOP:
    gb->direct.joypad_bits.start = 1;
    break;
  default:
    break;
  }
}

priv_t *GameBoy::data() { return &m_priv; }
