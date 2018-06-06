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
    Serial.println(dist);
    int distInt = (int) (dist * 100);
    if(dist > DISTMAX) {
      led1->setIntensity(0);
      led2->setIntensity(0);
    } else if(dist <= DISTMAX && dist > 0.55) {
      Serial.println("primoIf");
      int value = (int) map(distInt, 100, 55, 0, MAXINTENSITY);
      led1->setIntensity(value);
      led2->setIntensity(0);
    } else if(dist <= 0.55 && dist > 0.10) {
      Serial.println("secondoIf");
      int value = (int) map(distInt, 55, 10, 0, MAXINTENSITY);
      led1->setIntensity(MAXINTENSITY);
      led2->setIntensity(value);
    } else if(dist <= DISTMIN) {
      Serial.println("OK CAN STOP");
       if(MsgService.isMsgAvailable()) {
        if(MsgService.receiveMsg()->getContent() == "stop") {
          state = STP;
          led1->setIntensity(0);
          led2->setIntensity(0);
          Serial.println("ricevuto");
        }
      }
    }
    
  }
}

