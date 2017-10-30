#include "IOController.h"
#include <LogHelper.h>

#include "Pins.h"

IOController::IOController() : AbstractIntervalTask(1000) {
  for (uint8_t i=0;i<STATE_COUNT;i++) ioStates[i].init(0, false);
}

void IOController::init() {
  pinMode(PIN_BUILTIN_LED, OUTPUT);

  for (uint8_t i=0;i<STATE_COUNT;i++) pinMode(IO_PIN_BASE + i, OUTPUT);
}

void IOController::update() {
  if (digitalRead(PIN_BUILTIN_LED)==HIGH) {
    digitalWrite(PIN_BUILTIN_LED, LOW);
  } else {
    digitalWrite(PIN_BUILTIN_LED, HIGH);    
  }
}

void IOController::setState(uint8_t index, bool state) {
  if (index<STATE_COUNT) {
    LOG_PRINT(F("IO State "));
    LOG_PRINT(index);
    LOG_PRINT(F("->"));
    LOG_PRINTLN(state);
    ioStates[index].setValue(state);
  }
}

void IOController::simulateState(uint8_t index, bool state) {
  if (index<STATE_COUNT) {
    LOG_PRINT(F("Simulating IO State "));
    LOG_PRINT(index);
    LOG_PRINT(F("->"));
    LOG_PRINTLN(state);
    ioStates[index].setSimulatedValue(state);
  }
}
