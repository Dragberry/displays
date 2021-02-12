#include <displays/display.hpp>
#include <displays/font5x8.hpp>

Display::Display(DisplayInterface *const interface) :
    interface(interface) {
}

void Display::init() {
  interface->init();
  clear();
}

void Display::set_cursor(uint8_t x, uint8_t y) {
  interface->set_cursor(x, y);
}

void Display::clear() {
  register uint32_t i, j;
  for (i = 0; i < interface->row_height; i++) {
    interface->set_cursor(0, i);
    for (j = 0; j < interface->pixel_width; j++) {
      interface->write_data(0x00);
    }
  }

  interface->set_cursor(0, 0);
}

void Display::fill() {
  register uint32_t i, j;
  for (i = 0; i < interface->row_height; i++) {
    interface->set_cursor(0, i);
    for (j = 0; j < interface->pixel_width; j++) {
      interface->write_data(0xff);
    }
  }

  interface->set_cursor(0, 0);
}

void Display::put_char(const char c) {
  register uint32_t i;
  for (i = 0; i < 5; i++) {
    interface->write_data(FONT5x8[(c * 5) + i]);
  }
  interface->write_data(0x00);
}

void Display::put_string(const char *str) {
  char c;
  while ((c = (*str++))) {
    put_char(c);
  }
}

void Display::put_bar(const uint8_t size, const uint8_t filled, const uint8_t section_width) {
  register uint32_t i;
  uint8_t total_width = size * section_width;
  uint8_t total_filled_width = filled * section_width;
  interface->write_data(0x7F);
  for (i = 0; i < total_width; i++) {
    if (i < total_filled_width) {
      interface->write_data((i + 1) % section_width ? 0x7F : 0x41);
    } else {
      interface->write_data(0x41);
    }
  }
  interface->write_data(0x7F);
}
