#include <displays/jlx12864_display_interface.hpp>

void JLX12864DisplayInterface::init() {
  cbi(CS);
  cbi(RST);
  sbi(RST);
  write_command(0xe2);
  write_command(0x2c);
  write_command(0x2e);
  write_command(0x2f);
  write_command(0x23);
  write_command(0x81);
  write_command(0x28);
  write_command(0xa2);
  write_command(0xc8);
  write_command(0xa0);
  write_command(0x40);
  write_command(0xaf);
  write_command(0xa7);
  write_command(0xa4);
  sbi(CS);
}

void JLX12864DisplayInterface::set_cursor(uint8_t x, uint8_t y) {
  cbi(CS);
  write_command(0xb0 + y);
  write_command(((x >> 4) & 0x0f) + 0x10);
  write_command(x & 0x0f);
}

void JLX12864DisplayInterface::write_command(uint8_t command) {
  register uint32_t i;
  cbi(CS);
  cbi(RS);
  for (i = 0; i < 8; i++) {
    cbi(SCK);
    if (command & 0x80) {
      sbi(SDA);
    } else {
      cbi(SDA);
    }
    sbi(SCK);
    command <<= 1;
  }
}

void JLX12864DisplayInterface::write_data(uint8_t data) {
  register uint32_t i;
  cbi(CS);
  sbi(RS);
  for (i = 0; i < 8; i++) {
    cbi(SCK);
    if (data & 0x80) {
      sbi(SDA);
    } else {
      cbi(SDA);
    }
    sbi(SCK);
    data <<= 1;
  }
}
