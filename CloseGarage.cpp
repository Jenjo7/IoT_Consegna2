#include "CloseGarage.h"
#include "Arduino.h"
#include "config.h"

extern volatile State state;
int intensitys = MAXINTENSITY;

CloseGarage::CloseGarage(int led) {
  this->pin = led;
}

void CloseGarage::init(int period) {
  Task::init(period);
  fadeLed = new LedExt(pin, 0);
  fadeLed->switchOn();
}

void CloseGarage::tick() {
  if(state == CLS) {
    if(intensitys >= 0) {
//     fadeLed->switchOn();
       Serial.println(intensitys == MAXINTENSITY ? "close" : "");
       Serial.println(intensitys);
       fadeLed->setIntensity(intensitys);
       intensitys -= BRIGHT;
    } else {
      intensitys = MAXINTENSITY;
      state = INI;
    }
  }
}

