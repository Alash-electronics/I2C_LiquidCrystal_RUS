# I2C_LiquidCrystal_RUS

> 🌐 **English** | [Русский](README_ru.md)

Arduino library that adds Cyrillic (Russian) and Kazakh-specific character support to I2C/parallel character LCDs. It extends [LiquidCrystal_I2C](https://github.com/Alash-electronics/LiquidCrystal_I2C) (I2C wiring) or the standard `LiquidCrystal` library (10-pin wiring) with UTF-8 decoding and on-the-fly custom-glyph loading, so `lcd.print("Привет")` or `lcd.print("Әлем")` renders correctly on a 16x2/20x4 HD44780-style display that has no built-in Cyrillic character set.

## Why this exists

Standard HD44780 LCD controllers ship with a Japanese/Western character ROM — there is no Cyrillic, and no Kazakh-specific letters (Ә, І, Ң, Ғ, Ү, Ұ) at all. This library works around that by:

- Decoding incoming UTF-8 text to Unicode code points.
- Mapping visually-identical Cyrillic letters (А, В, Е, К, М, Н, О, Р, С, Т, Х, …) to their existing Latin glyphs in the LCD's built-in ROM.
- For the remaining ~50 Cyrillic and Kazakh letters that have no Latin look-alike, generating an 8x8 bitmap on the fly and loading it into one of the LCD's 8 programmable CGRAM character slots, reusing slots as the visible text scrolls.

## Requirements

- [LiquidCrystal_I2C](https://github.com/Alash-electronics/LiquidCrystal_I2C) library installed (for I2C wiring), or the built-in Arduino `LiquidCrystal` library (for direct 10-pin wiring).

## Usage

You must `#define _LCD_TYPE` **before** including the library — the build fails with a clear error otherwise.

```cpp
// 1 = I2C wiring, 2 = direct 10-pin wiring
#define _LCD_TYPE 1

#include <I2C_LiquidCrystal_RUS.h>

I2C_LiquidCrystal_RUS lcd(0x27, 16, 2); // I2C address, columns, rows

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Привет, мир!");
}

void loop() {}
```

Pin reference:

| Board | SDA | SCL |
|---|---|---|
| Arduino Uno/Nano | A4 | A5 |
| ESP8266 | D2 (4) | D1 (5) |
| ESP8266-01 | 0 | 2 |
| ESP32 | 21 | 22 |

## Examples

- `HelloWorld_I2C` / `HelloWorld_without_I2C` — minimal init + print
- `Custom_I2C_example` / `Custom_without_i2c_example` — custom character slots
- `I2C_scanner` — find your display's I2C address
- `SerialToLCD_I2C` / `SerialToLCD_without_i2c` — echo Serial input to the display
- `With_I2C_2Displays` — driving two displays at once

## Other Arduino libraries from Alash-electronics

[github.com/Alash-electronics](https://github.com/Alash-electronics)
