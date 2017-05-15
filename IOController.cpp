#include "IOController.h"

IOController::IOController() : AbstractIntervalTask(1000) {
  
}

void IOController::init() {
  //pinMode(D4, OUTPUT);
}

void IOController::update() {
  /*
  if (digitalRead(D4)==HIGH) {
    digitalWrite(D4, LOW);
  } else {
    digitalWrite(D4, HIGH);    
  }*/
}

