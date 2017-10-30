#ifndef DISPLAYCONTROLLER_H
#define DISPLAYCONTROLLER_H

#include <AbstractIntervalTask.h>

class DisplayController : public AbstractIntervalTask {
public:
  DisplayController();

  void init();

  void update();

private:

};


#endif   // DISPLAYCONTROLLER_H
