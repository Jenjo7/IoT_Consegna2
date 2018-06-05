#ifndef __STOP__
#define __STOP__

#include "Task.h"
#include "Led.h"
#include "ProximitySensor.h"
#include "Button.h"

class Stop: public Task {

private:
  int pin;
  Light* led;
  ProximitySensor* prox;
  Button* cls;

public:

  Stop(int pin, int echo, int trig);  
  void init(int period);  
  void tick();
};

#endif
