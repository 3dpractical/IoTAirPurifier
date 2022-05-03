#include "Essential.h"
#include "Remote.h"
#include "Network.h"

void setup() {
  //All I/O Activation ===========================================
  digitalWrite(UV_LED, LOW);
  digitalWrite(MIST_MAKER, LOW);
  digitalWrite(O3_GENERATOR, HIGH);

  //Serial initialization =========================================
  Serial.begin(115200);
  Serial2.begin(9600);

  //All I/O & Network initialization ==============================
  TFT_init();
  sensorInit();
  networkInit();
  actuatorInit();
  IRRemote_init();
}

void loop() {
  //Lv. 1 logic flow ==============================================
  IRRemote_read();
  buttonScan();

  //5s routine ====================================================
  presentTick = millis();
  if (presentTick - prevTick >= interval) {
    readSensor();
    TFT_printStream();
    logicFlow(false);
    DB_stream();
    DB_decoder();
    prevTick = presentTick;
    if (flag != 4) {
      if (O3_State == true) {
        digitalWrite(O3_GENERATOR, LOW);
        O3_State = false;
      } else if (O3_State == false) {
        digitalWrite(O3_GENERATOR, HIGH);
        O3_State = true;
      }
    } else {
      digitalWrite(O3_GENERATOR, HIGH);
    }
  }
}
