#ifndef INC_DISPLAYS_WD_G0906H_DISPLAY_INTERFACE_HPP_
#define INC_DISPLAYS_WD_G0906H_DISPLAY_INTERFACE_HPP_

#include <displays/display_interface.hpp>

class WD_G0906DisplayInterface : public DisplayInterface {
private:
  const uint16_t CS;
  const uint16_t RST;
  const uint16_t SDA;
  const uint16_t SCK;

public:
  WD_G0906DisplayInterface(
      volatile uint32_t *const PORT,
      const uint16_t CS,
      const uint16_t RST,
      const uint16_t SDA,
      const uint16_t SCK
      ) :
      DisplayInterface(96, 68, PORT),
      CS(CS), RST(RST), SDA(SDA), SCK(SCK) {
  }

  void init();

  void write_data(uint8_t byte);

  void write_command(uint8_t byte);

  void set_cursor(uint8_t x, uint8_t y);
};
#endif
