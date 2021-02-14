#ifndef INC_DISPLAYS_SSD1306_DISPLAY_INTERFACE_HPP_
#define INC_DISPLAYS_SSD1306_DISPLAY_INTERFACE_HPP_

#include <displays/display_interface.hpp>

class I2C {
public:
  virtual void send(uint8_t address, uint8_t *data, uint8_t length) = 0;
};

class SSD1306DisplayInterface : public DisplayInterface {
private:
  I2C *const i2c;
  const uint8_t address;

public:
  SSD1306DisplayInterface(I2C *const i2c, const uint8_t address = 0x3C, const uint8_t height = 64) :
      DisplayInterface(128, height),
      i2c(i2c), address(address) {
  }

public:
  void init();

  void write_data(uint8_t byte);

  void write_command(uint8_t byte);

  void set_cursor(uint8_t x, uint8_t y);
};

#endif
