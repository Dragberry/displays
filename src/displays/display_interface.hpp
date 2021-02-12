#ifndef INC_DISPLAYS_DISPLAY_INTERFACE_HPP_
#define INC_DISPLAYS_DISPLAY_INTERFACE_HPP_

#include <stdint.h>

class DisplayInterface {
protected:
  volatile uint32_t *const port;

  inline
  void sbi(const uint16_t bit) {
    *port |= (1 << bit);
  }

  inline
  void cbi(const uint16_t bit) {
    *port &= ~(1 << bit);
  }

  inline
  void delay(uint16_t time) {
    while (time--);
  }

public:
  const uint8_t pixel_width;
  const uint8_t pixel_height;
  const uint8_t row_height;

  DisplayInterface(uint8_t pixel_width, uint8_t pixel_height, volatile uint32_t *const port) :
    port(port),
    pixel_width(pixel_width),
    pixel_height(pixel_height),
    row_height((pixel_height + 7) / 8) {
  }

  virtual void init() = 0;

  virtual void write_data(uint8_t byte) = 0;

  virtual void write_command(uint8_t byte) = 0;

  virtual void set_cursor(uint8_t x, uint8_t y) = 0;
};

#endif
