#ifndef Essential.h
#define Essential.h

// ================= IO Pin & Comm. Address =================
// Generic Button, remote & Water level sensor ==============
#define BUTTON0           26
#define BUTTON1           14
#define WATERLEVEL        34
#define REMOTE_PIN        13

//MQ135 & MQ131 =============================================
#define MQ135_PIN         36
#define MQ131_PIN         39

// Comm. based sensor addresses =============================
#define MCP9808_ADDR      0x18
#define BME280_ADDR       0x76

//FAN & other out Pin =======================================
#define FAN               25
#define MIST_MAKER        32
#define UV_LED            27
#define O3_GENERATOR      33

#define FAN_FREQ    3000
#define CHANNEL     0
#define RESOLUTION  8

#define CO2_GOOD_AQI           (co2 >= 0.0000 && co2 <= 400.00)
#define CO2_SATISFACTORY_AQI   (co2 >= 401.00 && co2 <= 1000.0)
#define CO2_MODERATELY_AQI     (co2 >= 1000.1 && co2 <= 2000.0)
#define CO2_POOR_AQI           (co2 >= 2000.1 && co2 <= 5000.0)

#define CO_GOOD_AQI            (co >= 0.00 && co <= 0.870)
#define CO_SATISFACTORY_AQI    (co >= 0.96 && co <= 1.750)
#define CO_MODERATELY_AQI      (co >= 1.83 && co <= 8.730)
#define CO_POOR_AQI            (co >= 8.82 && co <= 14.84)

#define NOX_GOOD_AQI           (nox >= 0.00 && nox <= 0.00)
#define NOX_SATISFACTORY_AQI   (nox <= 0.00 && nox >= 0.00)
#define NOX_MODERATELY_AQI     (nox >= 0.00 && nox <= 0.00)
#define NOX_POOR_AQI           (nox >= 0.10 && nox <= 0.65)

#define O3_GOOD_AQI            (o3 >= 0.0000 && o3 <= 0.0059)
#define O3_SATISFACTORY_AQI    (o3 >= 0.0060 && o3 <= 0.0075)
#define O3_MODERATELY_AQI      (o3 >= 0.0076 && o3 <= 0.0095)
#define O3_POOR_AQI            (o3 >= 0.0096 && o3 <= 0.1150)

#define PM25_GOOD_AQI          (pm25 >= 0.00 && pm25 <= 15.40)
#define PM25_SATISFACTORY_AQI  (pm25 >= 15.5 && pm25 <= 40.40)
#define PM25_MODERATELY_AQI    (pm25 >= 40.5 && pm25 <= 65.40)
#define PM25_POOR_AQI          (pm25 >= 65.5 && pm25 <= 150.4)

String stringMode;
uint8_t score_AQI, score_NOX, score_CO2, score_CO, score_PM25, score_O3, wifiTick;
int8_t flag, fan[3];
String modeIndex, AQI;
int16_t pm1, pm25, pm10;
uint8_t automaticControl, __i__, __j__;
long presentTick, prevTick, interval = 5000;
float temp, hum, nox, co, co2, level;
double o3;
bool O3_State = true, levelIndex = false;
uint32_t remote_up, remote_down, remote_zero, remote_value;


#include "PMS.h"
#include "MQxx.h"
#include "BME280.h"
#include "Remote.h"
#include "Network.h"
#include "MCP9808.h"
#include "Interface.h"

void DB_decoder() {
  if (modeIndex == "low")
    flag = 0;
  else if (modeIndex == "normal")
    flag = 1;
  else if (modeIndex == "high")
    flag = 2;
  else if (modeIndex == "auto")
    flag = 3;
  else if (modeIndex == "idle")
    flag = 4;
}

void logicFlow(bool debug) {
  if (CO2_GOOD_AQI)
    score_CO2 = 4;
  else if (CO2_SATISFACTORY_AQI)
    score_CO2 = 3;
  else if (CO2_MODERATELY_AQI)
    score_CO2 = 2;
  else if (CO2_POOR_AQI)
    score_CO2 = 1;

  if (CO_GOOD_AQI)
    score_CO = 4;
  else if (CO_SATISFACTORY_AQI)
    score_CO = 3;
  else if (CO_MODERATELY_AQI)
    score_CO = 2;
  else if (CO_POOR_AQI)
    score_CO = 1;

  if (O3_GOOD_AQI)
    score_O3 = 4;
  else if (O3_SATISFACTORY_AQI)
    score_O3 = 3;
  else if (CO2_MODERATELY_AQI)
    score_O3 = 2;
  else if (CO2_POOR_AQI)
    score_O3 = 1;

  if (NOX_GOOD_AQI)
    score_NOX = 4;
  else if (NOX_SATISFACTORY_AQI)
    score_NOX = 3;
  else if (NOX_MODERATELY_AQI)
    score_NOX = 2;
  else if (NOX_POOR_AQI)
    score_NOX = 1;

  if (PM25_GOOD_AQI)
    score_PM25 = 4;
  else if (PM25_SATISFACTORY_AQI)
    score_PM25 = 3;
  else if (PM25_MODERATELY_AQI)
    score_PM25 = 2;
  else if (PM25_POOR_AQI)
    score_PM25 = 1;

  score_AQI = score_CO2 + score_CO + score_PM25 + score_NOX + score_O3;

  if (score_AQI == 20 || score_AQI >= 16) {
    AQI = "Good";
    automaticControl = 30;
  } else if (score_AQI <= 15 || score_AQI >= 12) {
    AQI = "Satisfactory";
    automaticControl = 60;
  } else if (score_AQI <= 11 || score_AQI >= 9) {
    AQI = "Moderately";
    automaticControl = 90;
  } else if (score_AQI <= 8 || score_AQI >= 4 || score_AQI < 4) {
    AQI = "Poor";
    automaticControl = 100;
  }

  switch (flag) {
    case 0 :
      modeIndex = "low";
      ledcWrite(0, 30);
      digitalWrite(UV_LED, LOW);
      digitalWrite(MIST_MAKER, LOW);
      break;
    case 1 :
      modeIndex = "normal";
      ledcWrite(0, 60);
      digitalWrite(UV_LED, LOW);
      digitalWrite(MIST_MAKER, LOW);
      break;
    case 2 :
      modeIndex = "high";
      ledcWrite(0, 90);
      digitalWrite(UV_LED, LOW);
      digitalWrite(MIST_MAKER, LOW);
      break;
    case 3 :
      modeIndex = "auto";
      ledcWrite(0, automaticControl);
      digitalWrite(UV_LED, LOW);
      digitalWrite(MIST_MAKER, LOW);
      break;
    case 4 :
      modeIndex = "idle";
      ledcWrite(0, 0);
      digitalWrite(UV_LED, HIGH);
      digitalWrite(MIST_MAKER, HIGH);
      digitalWrite(O3_GENERATOR, HIGH);
      ledcWrite(0, 0);
      break;
  }

  if (debug == true) {
    Serial.print("AQI = ");
    Serial.println(AQI);

    Serial.print("Mode = ");
    Serial.println(modeIndex);
  }
}

void actuatorInit() {
  pinMode(MIST_MAKER, OUTPUT);
  pinMode(O3_GENERATOR, OUTPUT);
  pinMode(UV_LED, OUTPUT);
  ledcAttachPin(FAN, CHANNEL);
  ledcSetup(CHANNEL, FAN_FREQ, RESOLUTION);
}

void buttonScan() {
  if (digitalRead(BUTTON0) == LOW) {
    while (digitalRead(BUTTON0) == LOW)
      ;
    if (++flag > 4)
      flag = 0;
    switch (flag) {
      case 0 :
        modeIndex = "low";
        break;
      case 1 :
        modeIndex = "normal";
        break;
      case 2 :
        modeIndex = "high";
        break;
      case 3 :
        modeIndex = "auto";
        break;
      case 4 :
        modeIndex = "idle";
        break;
    }
    DB_parseMode();
  } else if (digitalRead(BUTTON1) == LOW) {
    while (digitalRead(BUTTON1) == LOW)
      ;
    if (--flag < 0)
      flag = 4;
    switch (flag) {
      case 0 :
        modeIndex = "low";
        break;
      case 1 :
        modeIndex = "normal";
        break;
      case 2 :
        modeIndex = "high";
        break;
      case 3 :
        modeIndex = "auto";
        break;
      case 4 :
        modeIndex = "idle";
        break;
    }
    DB_parseMode();
  }
}

PMS pms(Serial2);
PMS::DATA data;

void ZH03_readPM25 (bool debug) {
  if (pms.read(data)) {
    pm25 = data.PM_AE_UG_2_5;
    if (debug == true) {
      Serial.print("PM2.5 = ");
      Serial.println(pm25);
    }
  }
}

void sensorInit() {
  TFT_init();
  MQxx_init();
  BME280_init();
  actuatorInit();
  IRRemote_init();
  MCP9808_init();

  pinMode(BUTTON0, INPUT_PULLUP);
  pinMode(BUTTON1, INPUT_PULLUP);
}

void Level_read(bool debug) {
  float raw = analogRead(WATERLEVEL);
  level = map(raw, 0, 4095, 0, 100);
  if (debug == true) {
    Serial.print("Water Level = ");
    Serial.println(level);
  }
}

void readSensor() {
  MQxx_readO3(true);
  MQxx_readNOx(false);
  MQxx_readCO(false);
  MQxx_readCO2(false);
  ZH03_readPM25(false);
  Level_read(false);
  BME280_readHum(false);
  MCP9808_readTemp(false);
}

#endif
