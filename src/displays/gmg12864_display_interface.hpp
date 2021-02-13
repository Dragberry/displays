#ifndef INC_JLX12864_DISPLAY_INTERFACE_HPP_
#define INC_JLX12864_DISPLAY_INTERFACE_HPP_

#include <displays/display_interface.hpp>

class GMG12864DisplayInterface : public DisplayInterface {
private:
  const uint16_t CS;
  const uint16_t RST;
  const uint16_t RS;
  const uint16_t SDA;
  const uint16_t SCK;

public:
  GMG12864DisplayInterface(
      volatile uint32_t *const PORT,
      const uint16_t CS,
      const uint16_t RST,
      const uint16_t RS,
      const uint16_t SDA,
      const uint16_t SCK
      ) :
      DisplayInterface(128, 64, PORT),
      CS(CS), RST(RST), RS(RS), SDA(SDA), SCK(SCK) {
  }

public:
  void init();

  void write_data(uint8_t byte);

  void write_command(uint8_t byte);

  void set_cursor(uint8_t x, uint8_t y);
};

#endif
