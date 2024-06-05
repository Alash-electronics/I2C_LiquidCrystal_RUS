// Простой пример подключения дисплея по шине I2C для печати на экране с Монитора порта

// Определение типа подключения дисплея:
               // 1 - через шину I2C
               // 2 - без I2C шины. 
#define _LCD_TYPE 1 // Обязательно указывать ДО подключения библиотеки,
// иначе возникнет ошибка при компиляции: "LCD type connect has not been declared"

#include <I2C_LiquidCrystal_RUS.h> // Импортируем библиотеку

// Создание объекта lcd с адресом 0x27, размером 16x2
I2C_LiquidCrystal_RUS lcd(0x27, 16, 2);

void setup() {
  lcd.init(); // Инициализация LCD
  // Для Arduino: A4 - SDA, A5 - SCL
  // Для ESP8266: 4(D2) - SDA, 5(D1) - SCL
  // Для ESP8266-01 I2C: 0 - SDA, 2 - SCL
  // Для ESP32: D21 - SDA, D22 - SCL

  // Печать сообщения на LCD
  lcd.backlight(); // Включение подсветки
  lcd.print("Ввод с монитора"); // Печать текста
  lcd.setCursor(5, 1); // Установка курсора в позицию (5, 1)
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
