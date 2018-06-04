#ifndef __CLOSEGARAGE__
#define __CLOSEGARAGE__

#include "Task.h"
#include "LedExt.h"

class CloseGarage: public Task {

  int pin;
  LedExt* fadeLed;

public:

  CloseGarage(int pin);  
  void init(int period);  
  void tick();
};

#endif
