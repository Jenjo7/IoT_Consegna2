#ifndef __PARKING__
#define __PARKING__

#include "Task.h"
#include "LedExt.h"
#include "Button.h"
#include "ProximitySensor.h"

class Parking: public Task {

private:
  LedExt* led1;
  LedExt* led2;
  LedExt* lr;
  Button* cls;
  Button* touch;
  ProximitySensor* prox;
  

public:
  Parking(int led1, int led2, int lr, int btnClose, int btnTouch, int proxTrig, int proxEcho);  
  void init(int period);  
  void tick();
};

#endif
