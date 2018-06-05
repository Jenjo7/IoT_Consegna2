#include "Stop.h"
#include "Arduino.h"
#include "config.h"

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
    int dist = (int) (prox->getDistance()*100);
    if(dist <= 10) {
      Serial.println("Ok");
      state = CLS;
    } 
  }
}

