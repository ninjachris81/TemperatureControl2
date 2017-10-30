/* META INFOS
target_package=arduino
target_platform=avr
board=mega
*/
#include <LogHelper.h>
#include <AbstractIntervalTask.h>
#include <AbstractTask.h>
#include <AbstractTriggerTask.h>
#include <TaskManager.h>

#include "Credentials.h"
#include "IOController.h"
#include "TemperatureController.h"
#include "SolarController.h"
#include "CommController.h"
#include "HeaterController.h"
#include "ConfigController.h"
#include "DisplayController.h"

TaskManager taskManager;

ConfigController configController;
IOController ioController;
TemperatureController temperatureController;
SolarController solarController;
CommController commController;
HeaterController heaterController;
DisplayController displayController;

void setup() {
  LOG_INIT();

  LOG_PRINTLN(F("INIT"));

  taskManager.registerTask(&configController);
  taskManager.registerTask(&ioController);
  taskManager.registerTask(&temperatureController);
  taskManager.registerTask(&solarController);
  taskManager.registerTask(&commController);
  taskManager.registerTask(&heaterController); 
  taskManager.registerTask(&displayController); 
  
  taskManager.init();
}

void loop() {
  taskManager.update();
  delay(100);
}
