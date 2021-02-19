# Dragberry Displays
This is a C++ template based library to use with small monochrome displays.
* Class `Display` is used for simple and fast operation as data is written directly to display.
* Class `GraphicDisplay<Width, Height>` is used to work with video memory which is stored in RAM.

### Supported:
* GMG12864-06D
* JLX12864G-086
* SSD1306 (OLED GME12864, GME12832)
* WD-G0906H (Nokia 1110, 96x68)

### The following example can be used for STM32:
* Instantiate the display interface implementation you need:
* Instantiate the display
* Initialize display
```
JLX12864DisplayInterface<__IO uint32_t, uint16_t> jxl12864 = JLX12864DisplayInterface<__IO uint32_t, uint16_t>(
    {&GPIOB->ODR, GPIO_ODR_ODR5_Pos},
    {&GPIOB->ODR, GPIO_ODR_ODR6_Pos},
    {&GPIOB->ODR, GPIO_ODR_ODR7_Pos},
    {&GPIOB->ODR, GPIO_ODR_ODR8_Pos},
    {&GPIOB->ODR, GPIO_ODR_ODR9_Pos}
);
Display display = Display(&jxl12864);
or
GraphicDisplay<128, 64> display = GraphicDisplay<128, 64>(&jxl12864);
display.init([]() -> void {
  // initialize your ports to output
});
```

### Class Display is used for simple and fast operation as data is written directly to display.
Initialization method. You must pass a function of signature void (void) to initialize your IO ports to output
```
void init(void (*init_io)(void))
```
Sets the cursor to position, where x is pixel, y - is 8-pixel page
```
void Display::set_cursor(uint8_t x, uint8_t y)
```
Clears the screen
```
void Display::clear()
```
Fills the screen
```
void Display::fill()
```
Puts the given 5X8 char to the cursor position
```
void Display::put_char(const char c)
```
Puts the given string t the cursor position
```
void Display::put_string(const char *str)
```
Puts the progress bar to the cursor position.
```
void Display::put_bar(const uint8_t size, const uint8_t filled, const uint8_t section_width)
```
