#include "Stop.h"
#include "Arduino.h"
#include "config.h"
#include "MsgService.h"

#include "Sonar.h"

extern volatile State state;

Stop::Stop(int ledd, int echo, int trig) {
  prox = new Sonar(echo, trig);
}

void Stop::init(int period) {
  Task::init(period);
}

void Stop::tick() {
  if(state == STP) {
    float dist = prox->getDistance();
    String msg = dist <= DISTMIN ? "K" : dist <= DISTCLOSE ? "G" : "F";
    state =  dist <= DISTCLOSE ? CLS : STP;
//    if(dist <= DISTMIN) {
////      Serial.flush();
//      MsgService.sendMsg("K");
//      Serial.flush();
//      state = CLS;
//    } 
//    
//    if(dist > DISTMIN) {
//      MsgService.sendMsg("F");
//    }
    MsgService.sendMsg(msg);
    Serial.flush();
  }
}

