#ifndef Network.h
#define Network.h

#include <WiFi.h>
#include <WiFiMulti.h>
#include "Essential.h"
#include <HTTPClient.h>

WiFiMulti wifiMulti;
HTTPClient http;

String payload;
String host = "airings.apibrawijaya.com";

uint8_t networkInit() {
  WiFi.begin("Api Brawijaya", "rahmannn");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (++wifiTick >= 10)
      break;
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  return 1;
}

void DB_parseMode() {
  if ((WiFi.status() == WL_CONNECTED)) {
    http.begin("http://airings.apibrawijaya.com/cek.php");
    if (http.GET() == HTTP_CODE_OK) {
      http.begin("http://airings.apibrawijaya.com/update.php?temp=" +  String(temp) + "&hum=" + String(hum) + "&nox=" + String(nox) + "&o3=" + String(o3, 4) + "&co=" + String(co) + "&co2=" + String(co2) + "&pm25=" + String(pm25) + "&airquality=" + AQI + "&mode=" + modeIndex);
      if (http.GET() && HTTP_CODE_OK) {
        if (http.getString() == "1") {
          Serial.println("Parsing data successful");
        } else {
          Serial.println("Parsing data failed");
        }
      }
    }
  } else
    Serial.println("Network error");
}

void DB_stream() {
  if ((WiFi.status() == WL_CONNECTED)) {
    http.begin("http://airings.apibrawijaya.com/cek.php");
    if (http.GET() == HTTP_CODE_OK) {
      modeIndex = http.getString();
      http.begin("http://airings.apibrawijaya.com/update.php?temp=" +  String(temp) + "&hum=" + String(hum) + "&nox=" + String(nox) + "&o3=" + String(o3, 4) + "&co=" + String(co) + "&co2=" + String(co2) + "&pm25=" + String(pm25) + "&airquality=" + AQI + "&mode=" + modeIndex);
      if (http.GET() && HTTP_CODE_OK) {
        if (http.getString() == "1") {
          Serial.println("Parsing data successful");
        } else {
          Serial.println("Parsing data failed");
        }
      }
    }
  } else
    Serial.println("Network error");
}

#endif
