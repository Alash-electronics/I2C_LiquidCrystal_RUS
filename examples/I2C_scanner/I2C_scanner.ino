/*
  I2C_scanner
  Этот скетч тестирует стандартные 7-битные адреса.
  Устройства с более высоким адресом бита могут быть неправильно обнаружены.
*/

#include "Wire.h"

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);
  Serial.println("\nI2C Scanner"); // Выводит сообщение о начале сканирования по шине I2C
}

void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning..."); // Выводит сообщение о начале сканирования

  nDevices = 0;
  for (address = 1; address < 127; address++ ) { // Перебирает адреса от 1 до 127
    Wire.beginTransmission(address); // Начинает передачу данных по шине I2C на определенный адрес
    error = Wire.endTransmission(); // Завершает передачу данных и проверяет наличие ошибок

    if (error == 0) { // Если ошибок нет
      Serial.print("I2C device found at address 0x"); // Выводит сообщение об обнаруженном устройстве
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++; // Увеличивает счетчик обнаруженных устройств
    }
    else if (error == 4) { // Если обнаружена ошибка
      Serial.print("Unknown error at address 0x"); // Выводит сообщение об ошибке
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n"); // Выводит сообщение о том, что устройства не обнаружены
  else
    Serial.println("done\n"); // Выводит сообщение о завершении сканирования

  delay(5000); // Ожидание перед следующим сканированием
}
