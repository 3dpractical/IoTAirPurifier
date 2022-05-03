#ifndef BME280.h
#define BME280.h

#include <Wire.h>
#include <Adafruit_BME280.h>
#include "Essential.h"

Adafruit_BME280 Hum;

void BME280_init() {
  bool stat = Hum.begin(BME280_ADDR);
  if (!stat) {
    Serial.println("BME280 Error");
    while(1);
  }
  delay(1000);
}


void BME280_readHum(bool debug) {
  hum = Hum.readHumidity();
  if (debug == true) {
    Serial.print("Humidity = ");
    Serial.println(hum);
  }
}

#endif
