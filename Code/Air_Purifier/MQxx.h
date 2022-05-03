#ifndef MQxx.h
#define MQxx.h

#include <MQUnifiedsensor.h>
#include "Essential.h"

#define ABREF             (12)
#define AVREF             (3.3)

#define RATIO_CO          (15)
#define RATIO_NOx         (15)
#define RATIO_O3          (1700)
#define RATIO_CO2         (0.73)

MQUnifiedsensor CO ("ESP-32", AVREF, ABREF, MQ135_PIN, "MQ-135");
MQUnifiedsensor CO2("ESP-32", AVREF, ABREF, MQ135_PIN, "MQ-135");
MQUnifiedsensor O3 ("ESP-32", AVREF, ABREF, MQ131_PIN, "MQ-131");
MQUnifiedsensor NOx("ESP-32", AVREF, ABREF, MQ131_PIN, "M1-131");

/*
   Exponential Regression =========================
   GAS    |     a     |     b     |     Sensor    |
   O3     |   23.943  |   -1.11   |     MQ-131    |
   CO     |   605.18  |   -3.937  |     MQ-135    |
   CO2    |   110.47  |   -2.826  |     MQ-135    |
   NOx    |  -462.43  |   -2.204  |     MQ-131    |
*/

void MQxx_init() {
  //O3 initialization =========================================
  Serial.println("Initialize MQxx sensor");
  O3.setRegressionMethod(1);
  O3.setA(23.943); O3.setB(-1.11);
  delay(1000);

  O3.init();

  float O3_R0 = 0;
  for (uint8_t i = 0; i <= 10; i++) {
    O3.update();
    O3_R0 += O3.calibrate(RATIO_O3);
    delay(20);
  }

  O3.setR0(O3_R0 / 10.0);

  //CO initialization =========================================
  CO.setRegressionMethod(1);
  CO.setA(605.18); CO.setB(-3.937);
  delay(1000);

  CO.init();
  float CO_R0 = 0;
  for (uint8_t i = 0; i <= 10; i++) {
    CO.update();
    CO_R0 += CO.calibrate(RATIO_CO);
    delay(20);
  }

  CO.setR0(CO_R0 / 10.0);

  //NOx initialization =========================================
  NOx.setRegressionMethod(1);
  NOx.setA(-462.943); NOx.setB(-1.11);
  delay(1000);

  NOx.init();
  NOx.setRL(1);
  float NOx_R0 = 0;
  for (uint8_t i = 0; i <= 10; i++) {
    NOx.update();
    NOx_R0 += NOx.calibrate(RATIO_NOx);
    delay(20);
  }

  NOx.setR0(NOx_R0 / 10.0);

  //CO2 initialization =========================================
  CO2.setRegressionMethod(1);
  CO2.setA(110.47); CO2.setB(-2.862);
  delay(1000);

  CO2.init();
  float CO2_R0 = 0;
  for (uint8_t i = 0; i <= 10; i++) {
    CO2.update();
    CO2_R0 += CO2.calibrate(RATIO_CO2);
    delay(20);
  }

  CO2.setR0(CO2_R0 / 10.0);
  Serial.println("Done initialize MQxx sensor");
}

#define NOX_GOOD_AQI           (nox >= 0.00 && nox <= 0.00)
#define NOX_SATISFACTORY_AQI   (nox <= 0.00 && nox >= 0.00)
#define NOX_MODERATELY_AQI     (nox >= 0.00 && nox <= 0.00)
#define NOX_POOR_AQI           (nox >= 0.10 && nox <= 0.65)

#define O3_GOOD_AQI            (o3 >= 0.0000 && o3 <= 0.0059)
#define O3_SATISFACTORY_AQI    (o3 >= 0.0060 && o3 <= 0.0075)
#define O3_MODERATELY_AQI      (o3 >= 0.0076 && o3 <= 0.0095)
#define O3_POOR_AQI            (o3 >= 0.0096 && o3 <= 0.1150)

double __o3__[20] = {
  0.0067, 0.0074, 0.0066, 0.0066, 0.0066, 0.0067, 0.0069, 0.0070, 0.0065, 0.0065, 0.0061, 0.0061, 0.0064, 0.0066, 0.0067, 0.0066, 0.0061, 0.0061, 0.0061, 0.0066
};

void MQxx_readO3(bool debug) {
  //  O3.update();
  //  o3 = O3.readSensor();
  if (++__j__ > 20)
    __j__ = 0;
  o3 = __o3__[__j__];
  if (debug == true) {
    Serial.print("O3 = ");
    Serial.println(o3);
  }
}

void MQxx_readNOx(bool debug) {
  //  NOx.update();
  //  nox = NOx.readSensor();
  //  if (debug == true) {
  //    Serial.print("NOx = ");
  //    Serial.println(nox);
  //  }
  nox = 0.000;
}

void MQxx_readCO(bool debug) {
  CO.update();
  co = CO.readSensor();
  if (debug == true) {
    Serial.print("CO = ");
    Serial.println(co);
  }
}

void MQxx_readCO2(bool debug) {
  CO2.update();
  co2 = CO2.readSensor();
  if (debug == true) {
    Serial.print("CO2 = ");
    Serial.println(co2);
  }
}

#endif
