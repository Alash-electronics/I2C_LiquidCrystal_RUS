/* Пример для подключения дисплея без i2c модуля для печати на экране с Монитора порта
 *  Схема подключения:
Пин RS LCD к цифровому пину 12
Пин Enable LCD к цифровому пину 11
Пин D4 LCD к цифровому пину 5
Пин D5 LCD к цифровому пину 4
Пин D6 LCD к цифровому пину 3
Пин D7 LCD к цифровому пину 2
Пин R/W LCD к земле
Пин VSS LCD к земле
Пин VCC LCD к 5V
Потенциометр 10К:
один конец к +5V, другой к земле
середину к пину VO LCD (пин 3)
*/

// Определение типа подключения дисплея:
               // 1 - через шину I2C
               // 2 - без I2C шины. 
#define _LCD_TYPE 2 //Обязательно указывать ДО подключения библиотеки,
// иначе возникнет ошибка при компиляции: "LCD type connect has not been declared"

#include <I2C_LiquidCrystal_RUS.h>

I2C_LiquidCrystal_RUS lcd(12, 11, 5, 4, 3, 2);

// Создание объекта lcd с пинами для подключения
//I2C_LiquidCrystal_RUS lcd(8, 9, 4, 5, 6, 7); // Для LCD Keypad Shield

void setup() {
  lcd.begin(16, 2);
  lcd.print("Ввод с монитора"); // Печать текста
  lcd.setCursor(5, 1); // Установка курсора в позицию (0, 1)
  lcd.print("порта"); // Печать текста

  // Инициализация последовательного порта
  Serial.begin(9600);
}

void loop() {
  unsigned char str;
  unsigned char w_str[2]; // Для расширенного символа UTF-8 два байта

  // При поступлении символов через последовательный порт...
  if (Serial.available())
  {
    // Подождем немного, чтобы полностью принять сообщение
    delay(100);
    // Очистим экран
    lcd.clear();
    lcd.setCursor(0, 0);
    // Прочитаем все доступные символы
    
    /*//Вариант для Win1251
    while (Serial.available() > 0)
    {
      // Выводим каждый символ на LCD
      str = Serial.read();
      lcd.print(lcd.ascii_win1251(str)); // Вывод на экран LCD, в т.ч. по-русски. Перевод из ASCII в Win1251.
    }*/
    
    // Вариант для UTF-8
    while (Serial.available() > 0)
    {
      // Выводим каждый символ на LCD
      w_str[0] = Serial.read();
      if(w_str[0] > 0x7F)
        w_str[1] = Serial.read(); // Если кириллица, то читаем второй байт
      lcd.print(lcd.ascii_utf8(w_str)); // Вывод на экран LCD, в т.ч. по-русски. Перевод из ASCII в UTF-8.
    }
    Serial.println();
  }
}
