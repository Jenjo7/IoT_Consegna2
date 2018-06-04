#ifndef __STOP__
#define __STOP__

#include "Task.h"
#include "Led.h"

class Stop: public Task {

private:
  int pin;
  Light* led;
  ProximitySensor* prox;
  

public:

  Stop(int pin);  
  void init(int period);  
  void tick();
};

#endif
