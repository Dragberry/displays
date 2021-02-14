#include <displays/ssd1306_display_interface.hpp>

void SSD1306DisplayInterface::init() {
  write_command(0xAE); //display off
  write_command(0x20); //Set Memory Addressing Mode
  write_command(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
  write_command(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
  write_command(0xC8); //Set COM Output Scan Direction
  write_command(0x00); //---set low column address
  write_command(0x10); //---set high column address
  write_command(0x40); //--set start line address
  write_command(0x81); //--set contrast control register
  write_command(0xFF);
  write_command(0xA1); //--set segment re-map 0 to 127
  write_command(0xA6); //--set normal display
  write_command(0xA8); //--set multiplex ratio(1 to 64)
  write_command(0x3F); //
  write_command(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
  write_command(0xD3); //-set display offset
  write_command(0x00); //-not offset
  write_command(0xD5); //--set display clock divide ratio/oscillator frequency
  write_command(0xF0); //--set divide ratio
  write_command(0xD9); //--set pre-charge period
  write_command(0x22); //
  write_command(0xDA); //--set com pins hardware configuration
  write_command(0x12);
  write_command(0xDB); //--set vcomh
  write_command(0x20); //0x20,0.77xVcc
  write_command(0x8D); //--set DC-DC enable
  write_command(0x14); //
  write_command(0xAF); //--turn on SSD1306 panel
}

void SSD1306DisplayInterface::write_data(uint8_t data) {
  uint8_t block[] = {0x40, data};
  i2c->send(address, block, 2);
}


void SSD1306DisplayInterface::write_command(uint8_t command) {
  uint8_t block[] = {0x00, command};
  i2c->send(address, block, 2);
}


void SSD1306DisplayInterface::set_cursor(uint8_t x, uint8_t y) {
  const uint8_t real_x = x + 2;
  write_command(0xB0 | y);
  write_command(0x10 | ((real_x >> 4) & 0x0F));
  write_command(0x00 | (real_x & 0x0F));
}

