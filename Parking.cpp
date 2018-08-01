#include "Parking.h"
#include "Arduino.h"
#include "Sonar.h"
#include "ButtonImpl.h"
#include "config.h"
#include "MsgService.h"

extern volatile State state;

Parking::Parking(int led1, int led2, int lr, int touch, int cls, int echo, int trig) {
  this->led1 = new LedExt(led1, 0);
  this->led2 = new LedExt(led2, 0);
  this->lr = new LedExt(lr);
  this->cls = new ButtonImpl(cls);
  this->touch = new ButtonImpl(touch);
  this->prox = new Sonar(echo, trig);
  
}

void Parking::init(int period) {
  Task::init(period);
  led1->switchOn();
  led2->switchOn();
}

void Parking::tick() {
  if(state == PRK) {
    float dist = prox->getDistance();
    int distInt = (int) (dist * 100);
    String msg;
    if(dist > DISTMAX) {
      led1->setIntensity(0);
      led2->setIntensity(0);
      msg = "D " + String(dist);
    } else if(dist <= DISTMAX && dist > DISTMIN) {
      int value1 = dist <= 0.55 ? MAXINTENSITY : (int) map(distInt, 100, 55, 0, MAXINTENSITY);
      int value2 = dist <= 0.55 ? (int) map(distInt, 55, 10, 0, MAXINTENSITY) : 0;
//      Serial.println(String(value1) + " " + String(value2));
      led1->setIntensity(value1);
      led2->setIntensity(value2);
      msg = "D " + String(dist);
    } else if(dist <= DISTMIN) {
//      Serial.println("OK CAN STOP");
//       if(MsgService.isMsgAvailable()) {
//        if(MsgService.receiveMsg()->getContent() == "stop") {
//          state = STP;
//          led1->setIntensity(0);
//          led2->setIntensity(0);
//          Serial.println("ricevuto");
//        }
//      }
        msg = "O";
    }
    if(cls->isPressed()) {
      if(dist <= DISTCLOSE) {
        state = STP;
        led1->setIntensity(0);
        led2->setIntensity(0);
      } else {
        msg = "F";
      }
    }
    if(touch->isPressed()) {
      msg = "T";
    }
    if(MsgService.isMsgAvailable()) {
        if(MsgService.receiveMsg()->getContent() == "stop") {
          state = STP;
          led1->setIntensity(0);
          led2->setIntensity(0);
        }
    }
    MsgService.sendMsg(msg);
    Serial.flush();
  }
}

