#include "config.h"
#include "Arduino.h"
#include "TimerOne.h"
#include "OpenGarage.h"

extern volatile State state;
int intensity = 0;
int inc = 0;

void changeState(State st) {
  inc = intensity = 0;
  state = st;
}


OpenGarage::OpenGarage(int ledPin, int pirPin){
  this->ledPin = ledPin;
  this->pirPin = pirPin;
}
  
void OpenGarage::init(int period){
  Task::init(period);
  fadeLed = new LedExt(ledPin, 0);  
  pir = new Pir(pirPin);
  fadeLed->switchOn();
}

void OpenGarage::tick() {
//OpeningGarage
  if(state == OPN) {
//    Serial.println(intensity == 0 ? "open" : "");
    if(intensity <= MAXINTENSITY) {
       fadeLed->switchOn();
//       Serial.println(intensity);
       fadeLed->setIntensity(intensity);
       intensity += BRIGHT;
//WaitForDetect
    } else {
      if(inc++ <= WAITTIME) {
        if(pir->isDetected()) {
          changeState(PRK);
        }
      } else {
        changeState(CLS);
      }
    }
  }
}



//void OpenGarage::fade() {
//  this->fadeLed->setIntensity(intensity);
//  intensity += BRIGHT;
//}

