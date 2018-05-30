#ifndef __INITTASK__
#define __INITTASK__

#include "Task.h"

class Init: public Task {

  public:

    Init();
    void init(int period);
    void tick();
};

#endif
