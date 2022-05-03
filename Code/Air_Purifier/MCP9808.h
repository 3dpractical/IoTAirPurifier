#ifndef MCP9808.h
#define MCP9808.h

#include <Wire.h>
#include "Adafruit_MCP9808.h"

Adafruit_MCP9808 Temp = Adafruit_MCP9808();

void MCP9808_init() {
  Temp.begin(MCP9808_ADDR);
  Temp.setResolution(3);
}

float MCP9808_read() {
  Temp.wake();
  float t = Temp.readTempC();
  Temp.shutdown_wake(1);
  return t;
}

void MCP9808_readTemp(bool debug) {
  Temp.wake();
  temp = Temp.readTempC();
  if (debug == true) {
    Serial.print("Temperature = ");
    Serial.println(temp);
  }
}

#endif
