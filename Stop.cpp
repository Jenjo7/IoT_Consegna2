#include "Stop.h"
#include "Arduino.h"
#include "config.h"

extern volatile State state;

Stop::Stop(int ledd) {
  
}

void Stop::init(int period) {
  Task::init(period);
}

void Stop::tick() {
  if(state == STP) {
    int dist = 
  }
}

