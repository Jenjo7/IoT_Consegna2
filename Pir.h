#ifndef __PIR__
#define __PIR__

#include "Arduino.h"
#include "DetectSensor.h"

class Pir: public DetectSensor {

  public:
    Pir(int pin);
    bool isDetected();
    
  private:
    int pin;
  
};

#endif
