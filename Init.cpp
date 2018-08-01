#include "Init.h"
#include "config.h"
#include "Arduino.h"
#include "MsgService.h"

extern volatile State state;

Init::Init() {
  MsgService.init();
}

void Init::init(int period) {
  Task::init(period);
//  MsgService.init();
}

void Init::tick() {
  //Serial.println("INIT");
  if(state == INI) {
    if(MsgService.isMsgAvailable()) {
      if(MsgService.receiveMsg()->getContent() == "open") {
        state = OPN;
        MsgService.sendMsg("W");
//        Serial.println("ricevuto");
    }
  }
    
  }
}

