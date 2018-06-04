#ifndef __OPENGARAGE__
#define __OPENGARAGE__

#include "Task.h"
#include "Led.h"
#include "LedExt.h"
#include "Pir.h"

class OpenGarage: public Task {

  private:
    int ledPin;
    int pirPin;
    Pir* pir;
    LedExt* fadeLed;
    void fade();
    
  public:
     OpenGarage(int ledPin, int pirPin);
     void init(int period);
     void tick();

};

#endif
