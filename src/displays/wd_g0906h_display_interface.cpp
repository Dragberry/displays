#include <displays/wd_g0906h_display_interface.hpp>

void WD_G0906DisplayInterface::init() {
  cbi(RST);
  delay(24000);
  write_command(0xE2); // Internal reset
  write_command(0xEB); // Thermal comp. on
  write_command(0x2F); // Supply mode
  write_command(0xA1); // Horisontal reverse: Reverse - 0xA9, Normal - 0xA1
  //write_command(0xC8); // Vertical reverse (comment if no need)
  write_command(0xA4); // Clear screen
  write_command(0xA6); // Positive - A7, Negative - A6
  write_command(0x90); // Contrast 0x90...0x9F

  write_command(0xAF); // Enable LCD
  sbi(RST);
}

void WD_G0906DisplayInterface::set_cursor(uint8_t x, uint8_t y) {
  write_command(0xB0 | (y & 0x0F));
  write_command(0x10 | (x >> 0x04));
  write_command(0x0F & x);
}

void WD_G0906DisplayInterface::write_command(uint8_t command) {
  register uint32_t i;
  cbi(CS);
  cbi(SDA);
  sbi(SCK);
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
  cbi(SCK);
  sbi(CS);
}

void WD_G0906DisplayInterface::write_data(uint8_t data) {
  register uint32_t i;
  cbi(CS);
  sbi(SDA);
  sbi(SCK);
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
