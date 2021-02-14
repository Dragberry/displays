#include <displays/gmg12864_display_interface.hpp>

void GMG12864DisplayInterface::init() {
  cbi(PORT, CS);
  cbi(PORT, RST);
  delay(50000);
  sbi(PORT, RST);
  delay(50000);

  write_command(0xE2);          // Internal reset
  write_command(0x28 | 0x04);   // turn on voltage converter (VC=1, VR=0, VF=0)
  write_command(0x28 | 0x06);   // turn on voltage regulator (VC=1, VR=1, VF=0)
  write_command(0x28 | 0x07);   // turn on voltage follower  (VC=1, VR=1, VF=1)
  write_command(0x20 | 0x07);   // set lcd operating voltage (regulator resistor, ref voltage resistor)
  write_command(0x81);          // Contrast level
  write_command(0x20);          // 0...63, 32 - default
  write_command(0xA0);          // ADC select (0xA0/vA1)
  write_command(0xA3);          // Bias (0xA2=9/0xA3=7)
  write_command(0xA6);          // Display (0xA6=NORMAL/0xA7=REVERSE)
  write_command(0xC8);          // COM output scan direction (0xC0=NORMAL/0xC8=REVERSE)
  write_command(0x40  | 0x00);  // Initial display line
  write_command(0xAF);          // Display (0xAF=ON/0xAE=OFF)
  write_command(0xA4);          // Display all points (0xA4=NO/0xA5=YES)
  delay(50000);
}

void GMG12864DisplayInterface::set_cursor(uint8_t x, uint8_t y) {
  write_command(0xb0 | y);
  write_command(0x10 | ((x >> 4) & 0x0F));
  write_command(0x00 | (x & 0x0F));
}

void GMG12864DisplayInterface::write_command(uint8_t command) {
  register uint32_t i;
  cbi(PORT, RS);
  for (i = 0; i < 8; i++) {
    cbi(PORT, SCK);
    if (command & 0x80) {
      sbi(PORT, SDA);
    } else {
      cbi(PORT, SDA);
    }
    sbi(PORT, SCK);
    command <<= 1;
  }
}

void GMG12864DisplayInterface::write_data(uint8_t data) {
  register uint32_t i;
  sbi(PORT, RS);
  for (i = 0; i < 8; i++) {
    cbi(PORT, SCK);
    if (data & 0x80) {
      sbi(PORT, SDA);
    } else {
      cbi(PORT, SDA);
    }
    sbi(PORT, SCK);
    data <<= 1;
  }
}
