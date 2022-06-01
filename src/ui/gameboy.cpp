#include "ui/gameboy.h"

#include <QDebug>
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
uint8_t gb_rom_read(struct gb_s *gb, const uint_fast32_t addr) {
  const struct priv_t *const p = (const struct priv_t *const)gb->direct.priv;
  return p->rom[addr];
}

/**
 * Returns a byte from the cartridge RAM at the given address.
 */
uint8_t gb_cart_ram_read(struct gb_s *gb, const uint_fast32_t addr) {
  const struct priv_t *const p = (const struct priv_t *const)gb->direct.priv;
  return p->cart_ram[addr];
}

/**
 * Writes a given byte to the cartridge RAM at the given address.
 */
void gb_cart_ram_write(struct gb_s *gb, const uint_fast32_t addr, const uint8_t val) {
  const struct priv_t *const p = (const struct priv_t *const)gb->direct.priv;
  p->cart_ram[addr] = val;
}

/**
 * Returns a pointer to the allocated space containing the ROM. Must be freed.
 */
uint8_t *read_rom_to_ram(const char *file_name) {
  FILE *rom_file = fopen(file_name, "rb");
  size_t rom_size;
  uint8_t *rom = NULL;

  if (rom_file == NULL)
    return NULL;

  fseek(rom_file, 0, SEEK_END);
  rom_size = ftell(rom_file);
  rewind(rom_file);
  rom = (uint8_t *)malloc(rom_size);

  if (fread(rom, sizeof(uint8_t), rom_size, rom_file) != rom_size) {
    free(rom);
    fclose(rom_file);
    return NULL;
  }

  fclose(rom_file);
  return rom;
}

void read_cart_ram_file(const char *save_file_name, uint8_t **dest, const size_t len) {
  FILE *f;

  /* If save file not required. */
  if (len == 0) {
    *dest = NULL;
    return;
  }

  /* Allocate enough memory to hold save file. */
  if ((*dest = (uint8_t *)malloc(len)) == NULL) {
    printf("%d: %s\n", __LINE__, strerror(errno));
    exit(EXIT_FAILURE);
  }

  f = fopen(save_file_name, "rb");

  /* It doesn't matter if the save file doesn't exist. We initialise the
   * save memory allocated above. The save file will be created on exit. */
  if (f == NULL) {
    memset(*dest, 0, len);
    return;
  }

  /* Read save file to allocated memory. */
  fread(*dest, sizeof(uint8_t), len, f);
  fclose(f);
}

void write_cart_ram_file(const char *save_file_name, uint8_t **dest, const size_t len) {
  FILE *f;

  if (len == 0 || *dest == NULL)
    return;

  if ((f = fopen(save_file_name, "wb")) == NULL) {
    puts("Unable to open save file.");
    printf("%d: %s\n", __LINE__, strerror(errno));
    exit(EXIT_FAILURE);
  }

  /* Record save file. */
  fwrite(*dest, sizeof(uint8_t), len, f);
  fclose(f);
}

void auto_assign_palette(struct priv_t *priv, uint8_t game_checksum) {
  size_t palette_bytes = 3 * 4 * sizeof(uint16_t);

  switch (game_checksum) {
  /* Balloon Kid and Tetris Blast */
  case 0x71:
  case 0xFF: {
    const uint16_t palette[3][4] = {
        {0x7FFF, 0x7E60, 0x7C00, 0x0000}, /* OBJ0 */
        {0x7FFF, 0x7E60, 0x7C00, 0x0000}, /* OBJ1 */
        {0x7FFF, 0x7E60, 0x7C00, 0x0000}  /* BG */
    };
    memcpy(priv->selected_palette, palette, palette_bytes);
    break;
  }

  /* Pokemon Yellow and Tetris */
  case 0x15:
  case 0xDB:
  case 0x95: /* Not officially */
  {
    const uint16_t palette[3][4] = {
        {0x7FFF, 0x7FE0, 0x7C00, 0x0000}, /* OBJ0 */
        {0x7FFF, 0x7FE0, 0x7C00, 0x0000}, /* OBJ1 */
        {0x7FFF, 0x7FE0, 0x7C00, 0x0000}  /* BG */
    };
    memcpy(priv->selected_palette, palette, palette_bytes);
    break;
  }

  /* Donkey Kong */
  case 0x19: {
    const uint16_t palette[3][4] = {
        {0x7FFF, 0x7E10, 0x48E7, 0x0000}, /* OBJ0 */
        {0x7FFF, 0x7E10, 0x48E7, 0x0000}, /* OBJ1 */
        {0x7FFF, 0x7E60, 0x7C00, 0x0000}  /* BG */
    };
    memcpy(priv->selected_palette, palette, palette_bytes);
    break;
  }

  /* Pokemon Blue */
  case 0x61:
  case 0x45:

  /* Pokemon Blue Star */
  case 0xD8: {
    const uint16_t palette[3][4] = {
        {0x7FFF, 0x7E10, 0x48E7, 0x0000}, /* OBJ0 */
        {0x7FFF, 0x329F, 0x001F, 0x0000}, /* OBJ1 */
        {0x7FFF, 0x329F, 0x001F, 0x0000}  /* BG */
    };
    memcpy(priv->selected_palette, palette, palette_bytes);
    break;
  }

  /* Pokemon Red */
  case 0x14: {
    const uint16_t palette[3][4] = {
        {0x7FFF, 0x3FE6, 0x0200, 0x0000}, /* OBJ0 */
        {0x7FFF, 0x7E10, 0x48E7, 0x0000}, /* OBJ1 */
        {0x7FFF, 0x7E10, 0x48E7, 0x0000}  /* BG */
    };
    memcpy(priv->selected_palette, palette, palette_bytes);
    break;
  }

  /* Pokemon Red Star */
  case 0x8B: {
    const uint16_t palette[3][4] = {
        {0x7FFF, 0x7E10, 0x48E7, 0x0000}, /* OBJ0 */
        {0x7FFF, 0x329F, 0x001F, 0x0000}, /* OBJ1 */
        {0x7FFF, 0x3FE6, 0x0200, 0x0000}  /* BG */
    };
    memcpy(priv->selected_palette, palette, palette_bytes);
    break;
  }

  /* Kirby */
  case 0x27:
  case 0x49:
  case 0x5C:
  case 0xB3: {
    const uint16_t palette[3][4] = {
        {0x7D8A, 0x6800, 0x3000, 0x0000}, /* OBJ0 */
        {0x001F, 0x7FFF, 0x7FEF, 0x021F}, /* OBJ1 */
        {0x527F, 0x7FE0, 0x0180, 0x0000}  /* BG */
    };
    memcpy(priv->selected_palette, palette, palette_bytes);
    break;
  }

  /* Donkey Kong Land [1/2/III] */
  case 0x18:
  case 0x6A:
  case 0x4B:
  case 0x6B: {
    const uint16_t palette[3][4] = {
        {0x7F08, 0x7F40, 0x48E0, 0x2400}, /* OBJ0 */
        {0x7FFF, 0x2EFF, 0x7C00, 0x001F}, /* OBJ1 */
        {0x7FFF, 0x463B, 0x2951, 0x0000}  /* BG */
    };
    memcpy(priv->selected_palette, palette, palette_bytes);
    break;
  }

  /* Link's Awakening */
  case 0x70: {
    const uint16_t palette[3][4] = {
        {0x7FFF, 0x03E0, 0x1A00, 0x0120}, /* OBJ0 */
        {0x7FFF, 0x329F, 0x001F, 0x001F}, /* OBJ1 */
        {0x7FFF, 0x7E10, 0x48E7, 0x0000}  /* BG */
    };
    memcpy(priv->selected_palette, palette, palette_bytes);
    break;
  }

  /* Mega Man [1/2/3] & others I don't care about. */
  case 0x01:
  case 0x10:
  case 0x29:
  case 0x52:
  case 0x5D:
  case 0x68:
  case 0x6D:
  case 0xF6: {
    const uint16_t palette[3][4] = {
        {0x7FFF, 0x329F, 0x001F, 0x0000}, /* OBJ0 */
        {0x7FFF, 0x3FE6, 0x0200, 0x0000}, /* OBJ1 */
        {0x7FFF, 0x7EAC, 0x40C0, 0x0000}  /* BG */
    };
    memcpy(priv->selected_palette, palette, palette_bytes);
    break;
  }

  default: {
    const uint16_t palette[3][4] = {
        {0x7FFF, 0x5294, 0x294A, 0x0000}, {0x7FFF, 0x5294, 0x294A, 0x0000}, {0x7FFF, 0x5294, 0x294A, 0x0000}};
    printf("No palette found for 0x%02X.\n", game_checksum);
    memcpy(priv->selected_palette, palette, palette_bytes);
  }
  }
}

void lcd_draw_line(struct gb_s *gb, const uint8_t pixels[160], const uint_least8_t line) {
  struct priv_t *priv = (struct priv_t *)gb->direct.priv;

  for (unsigned int x = 0; x < LCD_WIDTH; x++) {
    priv->fb[line][x] = priv->selected_palette[(pixels[x] & LCD_PALETTE_ALL) >> 4][pixels[x] & 3];
  }
}

/**
 * Handles an error reported by the emulator. The emulator context may be used
 * to better understand why the error given in gb_err was reported.
 */
void gb_error(struct gb_s *gb, const enum gb_error_e gb_err, const uint16_t val) {
  struct priv_t *priv = (struct priv_t *)gb->direct.priv;

  switch (gb_err) {
  case GB_INVALID_OPCODE:
    /* We compensate for the post-increment in the __gb_step_cpu
     * function. */
    fprintf(stdout, "Invalid opcode %#04x at PC: %#06x, SP: %#06x\n", val, gb->cpu_reg.pc - 1, gb->cpu_reg.sp);
    break;

  /* Ignoring non fatal errors. */
  case GB_INVALID_WRITE:
  case GB_INVALID_READ:
    return;

  default:
    printf("Unknown error");
    break;
  }

  fprintf(stderr, "Error. Press q to exit, or any other key to continue.");

  if (getchar() == 'q') {
    /* Record save file. */
    write_cart_ram_file("recovery.sav", &priv->cart_ram, gb_get_save_size(gb));

    free(priv->rom);
    free(priv->cart_ram);
    exit(EXIT_FAILURE);
  }

  return;
}

GameBoy::GameBoy() : m_gb() {
  m_priv = {.rom = NULL, .cart_ram = NULL};

  char *rom_file_name = (char *)"rom.gb";
  if (access(rom_file_name, F_OK) != 0) {
    qFatal("Rom file not found. Emulator won't work.");
    return;
  }

  m_priv.rom = read_rom_to_ram(rom_file_name);

  char *save_file_name;
  char *str_replace;
  const char extension[] = ".sav";

  save_file_name = (char *)malloc(strlen(rom_file_name) + strlen(extension) + 1);

  strcpy(save_file_name, rom_file_name);

  if ((str_replace = strrchr(save_file_name, '.')) == NULL || str_replace == save_file_name)
    str_replace = save_file_name + strlen(save_file_name);

  for (unsigned int i = 0; i <= strlen(extension); i++)
    *(str_replace++) = extension[i];

  m_gb = malloc(sizeof(struct gb_s));

  gb_init((struct gb_s *)m_gb, &gb_rom_read, &gb_cart_ram_read, &gb_cart_ram_write, &gb_error, &m_priv);

  read_cart_ram_file(save_file_name, &m_priv.cart_ram, gb_get_save_size((struct gb_s *)m_gb));
  gb_init_lcd((struct gb_s *)m_gb, &lcd_draw_line);

  auto_assign_palette(&m_priv, gb_colour_hash((struct gb_s *)m_gb));
}

void GameBoy::execute() { gb_run_frame((struct gb_s *)m_gb); }

priv_t *GameBoy::data() { return &m_priv; }
