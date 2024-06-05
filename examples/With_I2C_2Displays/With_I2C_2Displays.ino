//Пример для подключения двух дисплеев и более по шине I2C

// Определение типа подключения дисплея:
               // 1 - через шину I2C
               // 2 - без I2C шины. 
#define _LCD_TYPE 1 //Обязательно указывать ДО подключения библиотеки,
// иначе возникнет ошибка при компиляции: "LCD type connect has not been declared"

#include <I2C_LiquidCrystal_RUS.h> // Подключаем библиотеку

I2C_LiquidCrystal_RUS lcd1(0x27, 16, 2); // Создаем объект lcd1 с адресом 0x27, размером 16x2
I2C_LiquidCrystal_RUS lcd2(0x3F, 16, 2); // Создаем объект lcd2 с адресом 0x3F, размером 16x2

void setup() {
  String str;
  str = "Alash education"; // Строка для печати на обоих дисплеях

  lcd1.init(); // Инициализация LCD
  // Для Arduino: A4 - SDA, A5 - SCL
  // Для ESP8266: 4(D2) - SDA, 5(D1) - SCL
  // Для ESP8266-01 I2C: 0 - SDA, 2 - SCL
  // Для ESP32: D21 - SDA, D22 - SCL
  lcd2.init(); // Инициализация LCD №2
  
  // Печать сообщения на LCD №1
  lcd1.backlight(); // Включение подсветки на LCD №1
  lcd1.setCursor(0, 0); // Установка курсора на LCD №1 в позицию (0, 0)
  lcd1.print("Лучший туториал:"); // Печать текста на LCD №1
  lcd1.setCursor(0, 1); // Установка курсора на LCD №1 в позицию (0, 1)
  lcd1.print(str); // Печать строки на LCD №1

  // Печать сообщения на LCD №2
  lcd2.backlight(); // Включение подсветки на LCD №2
  lcd2.setCursor(1, 0); // Установка курсора на LCD №2 в позицию (2, 0)
  lcd2.print("Второй дисплей"); // Печать текста на LCD №2
  lcd2.setCursor(4, 1); // Установка курсора на LCD №2 в позицию (0, 1)
  lcd2.print("работает"); // Печать строки на LCD №2
}

void loop() {
}
