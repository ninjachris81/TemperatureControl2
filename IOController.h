#ifndef IOCONTROLLER_H
#define IOCONTROLLER_H

#include <AbstractIntervalTask.h>

class IOController : public AbstractIntervalTask {
  public:
    IOController();
  
    void init();

    void update();
};

#endif
