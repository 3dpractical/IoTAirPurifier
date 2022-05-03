#ifndef remote.h
#define remote.h

#include <IRremote.h>
#include "Essential.h"
#include "Network.h"

IRrecv irrecv(REMOTE_PIN);
decode_results results;

void IRRemote_init() {
  irrecv.enableIRIn();
}

void IRRemote_read() {
  if (irrecv.decode(&results)) {
    remote_value = results.value;
    irrecv.resume();
    if (remote_value == 0x1FEE01F) {
      flag = 0;
    } else if (remote_value == 0x1FE50AF) {
      flag = 1;
    } else if (remote_value == 0x1FED827) {
      flag = 2;
    } else if (remote_value == 0x1FEF807) {
      flag = 3;
    } else if (remote_value == 0x1FE48B7) {
      flag = 4;
    }
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

#endif
