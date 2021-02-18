#ifndef INC_DISPLAYS_DISPLAY_INTERFACE_HPP_
#define INC_DISPLAYS_DISPLAY_INTERFACE_HPP_

#include <stdint.h>

template <typename Port, typename Pin>
struct Output {
  Port * const port;
  const Pin pin;

  void set() {
    *port |= (1 << pin);
  }

  void clear() {
    *port &= ~(1 << pin);
  }
};

class DisplayInterface {
protected:
  inline static
  void delay(uint16_t time) {
    while (time--);
  }

public:
  const uint8_t width;
  const uint8_t height;
  const uint8_t rows;

  DisplayInterface(uint8_t width, uint8_t height) :
    width(width),
    height(height),
    rows((height + 7) / 8) {
  }

  virtual void init() = 0;

  virtual void write_data(uint8_t byte) = 0;

  virtual void write_command(uint8_t byte) = 0;

  virtual void set_cursor(uint8_t x, uint8_t y) = 0;
};

#endif
