#include <Arduino.h>
#include <SPI.h>

// Basically defaults besides 12Mhz
SPISettings settings(12000000, MSBFIRST, SPI_MODE0);

const uint32_t CS = 10;

void setup() {
  Serial.begin(MONITOR_SPEED);
  while (!Serial)
    ;
  Serial.print("Booted");
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
  SPI.begin();
  SPI.setClockDivider(0);
}

void loop() {
  SPI.beginTransaction(settings);
  digitalWrite(CS, LOW);
  delay(25);
  auto byte = SPI.transfer(0x00);
  Serial.println(byte, HEX);
  digitalWrite(CS, HIGH);
  SPI.endTransaction();
  delay(25);
}
