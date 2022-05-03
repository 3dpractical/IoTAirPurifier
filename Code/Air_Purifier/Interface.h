#ifndef Interface.h
#define Inteface.h

#include "SPI.h"
#include "TFT_eSPI.h"
#define TFT_GREY 0x7BEF

TFT_eSPI myGLCD = TFT_eSPI();

void TFT_init() {
  myGLCD.init();
  myGLCD.setRotation(3);
}

void TFT_printStream() {
  myGLCD.fillScreen(0x000000);

  myGLCD.drawRect(10, 10, 300, 220, TFT_WHITE);
  myGLCD.drawRect(10, 10, 300, 35, TFT_WHITE);

  myGLCD.drawLine(95, 44, 95, 210, TFT_WHITE);
  myGLCD.drawLine(160, 44, 160, 210, TFT_WHITE);
  myGLCD.drawLine(225, 44, 225, 210, TFT_WHITE);

  myGLCD.drawRect(10, 210, 300, 20, TFT_WHITE);
  myGLCD.drawRect(10, 130, 300, 100, TFT_WHITE);

  myGLCD.setTextColor(TFT_WHITE);

  myGLCD.drawCentreString("SYSTEM MONITOR", 160, 20, 2);

  myGLCD.drawCentreString("Air Quality", 53, 55, 2);
  myGLCD.drawCentreString("Index (AQI)", 53, 70, 2);

  myGLCD.drawCentreString("Temperature", 268, 55, 2);
  myGLCD.drawCentreString("(Celcius)", 268, 70, 2);

  myGLCD.drawCentreString("Humidity", 129, 55, 2);
  myGLCD.drawCentreString("(RH)", 129, 70, 2);

  myGLCD.drawCentreString("CO2", 194, 55, 2);
  myGLCD.drawCentreString("Intensity", 194, 67, 2);
  myGLCD.drawCentreString("(PPM)", 194, 83, 1);

  myGLCD.drawCentreString("NOx", 52, 140, 2);
  myGLCD.drawCentreString("Intensity", 52, 150, 2);
  myGLCD.drawCentreString("(PPM)", 52, 165, 1);

  myGLCD.drawCentreString("O3", 128, 140, 2);
  myGLCD.drawCentreString("Intensity", 128, 150, 2);
  myGLCD.drawCentreString("(PPM)", 128, 166, 1);

  myGLCD.drawCentreString("CO", 194, 140, 2);
  myGLCD.drawCentreString("Intensity", 194, 150, 2);
  myGLCD.drawCentreString("(PPM)", 194, 166, 1);

  myGLCD.drawCentreString("PM2.5", 268, 140, 2);
  myGLCD.drawCentreString("Intensity", 268, 150, 2);
  myGLCD.drawCentreString("(ug/m3)", 265, 166, 1);

  myGLCD.drawFloat(temp, 1, 244, 97, 4);
  myGLCD.drawFloat(hum, 1, 104, 97, 4);
  myGLCD.drawFloat(co2, 1, 176, 99, 2);

  myGLCD.drawFloat(nox, 4, 32, 180, 2);
  myGLCD.drawFloat(o3, 4, 107, 183, 2);
  myGLCD.drawFloat(co, 3, 174, 180, 2);
  myGLCD.drawFloat(pm25, 1, 250, 180, 4);

  uint16_t a;
  if (AQI == "Good" || AQI == "Poor")
    a = 4;
  else
    a = 2;
  myGLCD.drawCentreString(AQI, 53, 95, a);

  if (level <= 6) {
    switch (flag) {
      case 0 :
        myGLCD.drawCentreString("E | LOW MODE | AirIngs | UNIVERSITAS BRAWIJAYA", 160, 217, 1);
        break;
      case 1 :
        myGLCD.drawCentreString("E | NORMAL MODE | AirIngs | UNIVERSITAS BRAWIJAYA", 159, 217, 1);
        break;
      case 2 :
        myGLCD.drawCentreString("E | HIGH MODE | AirIngs | UNIVERSITAS BRAWIJAYA", 160, 217, 1);
        break;
      case 3 :
        myGLCD.drawCentreString("E | AUTO MODE | AirIngs | UNIVERSITAS BRAWIJAYA", 160, 217, 1);
        break;
      case 4 :
        myGLCD.drawCentreString("E | IDLE MODE | AirIngs | UNIVERSITAS BRAWIJAYA", 160, 217, 1);
        break;
    }
  } else if (level >= 9) {
    switch (flag) {
      case 0 :
        myGLCD.drawCentreString("F | LOW MODE | AirIngs | UNIVERSITAS BRAWIJAYA", 160, 217, 1);
        break;
      case 1 :
        myGLCD.drawCentreString("F | NORMAL MODE | AirIngs | UNIVERSITAS BRAWIJAYA", 159, 217, 1);
        break;
      case 2 :
        myGLCD.drawCentreString("F | HIGH MODE | AirIngs | UNIVERSITAS BRAWIJAYA", 160, 217, 1);
        break;
      case 3 :
        myGLCD.drawCentreString("F | AUTO MODE | AirIngs | UNIVERSITAS BRAWIJAYA", 160, 217, 1);
        break;
      case 4 :
        myGLCD.drawCentreString("F | IDLE MODE | AirIngs | UNIVERSITAS BRAWIJAYA", 160, 217, 1);
        break;
    }
  } else {
    switch (flag) {
      case 0 :
        myGLCD.drawCentreString("LOW MODE | AirIngs | UNIVERSITAS BRAWIJAYA", 160, 217, 1);
        break;
      case 1 :
        myGLCD.drawCentreString("NORMAL MODE | AirIngs | UNIVERSITAS BRAWIJAYA", 159, 217, 1);
        break;
      case 2 :
        myGLCD.drawCentreString("HIGH MODE | AirIngs | UNIVERSITAS BRAWIJAYA", 160, 217, 1);
        break;
      case 3 :
        myGLCD.drawCentreString("AUTO MODE | AirIngs | UNIVERSITAS BRAWIJAYA", 160, 217, 1);
        break;
      case 4 :
        myGLCD.drawCentreString("IDLE MODE | AirIngs | UNIVERSITAS BRAWIJAYA", 160, 217, 1);
        break;
    }
  }
}

#endif
