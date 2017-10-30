#ifndef IOCONTROLLER_H
#define IOCONTROLLER_H

#include <AbstractIntervalTask.h>
#include <Property.h>

#define STATE_COUNT 4
#define IO_PIN_BASE 40

class IOController : public AbstractIntervalTask {
public:
  IOController();

  void init();

  void update();

  void setState(uint8_t index, bool state);

  void simulateState(uint8_t index, bool state);

private:
  Property<bool> ioStates[STATE_COUNT];


};

#endif
