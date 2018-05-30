#include "Init.h"
#include "config.h"
#include "Arduino.h"
#include "MsgService.h"

extern volatile State state;

Init::Init() {
  
}

void Init::init(int period) {
  Task::init(period);
}

void Init::tick() {
  if(MsgService.isAviable()) {
    if(MsgService.receiveMsg().getContent() == "open") {
      state = PRK;
    }
  }
}

