#include "TemperatureController.h"
#include <LogHelper.h>

TemperatureController::TemperatureController() : AbstractIntervalTask(TEMP_INTERVAL_MS) {
  oneWire = new OneWire(PIN_TEMP_SENSOR);
  sensors = new DallasTemperature(oneWire);
  for (uint8_t i=0;i<SENSOR_COUNT;i++) tempValues[i] = DEVICE_DISCONNECTED_C;
}

TemperatureController::~TemperatureController() {
  delete oneWire;
  delete sensors;
}

void TemperatureController::init() {
  sensors->begin();
  sensors->setWaitForConversion(false);
}

void TemperatureController::update() {
  if (foundSensors!=SENSOR_COUNT) {
    byte addr[8];
    
    if (!oneWire->search(addr)) {
      LOG_PRINTLN(F("no 1-wire devices"));
      sensors->begin();
      return;
    }
    
    LOG_PRINT(F("Devices: "));
    LOG_PRINTLNF(sensors->getDeviceCount(), DEC);
    foundSensors = sensors->getDeviceCount();
  } else {
    for (uint8_t i=0;i<SENSOR_COUNT;i++) {
      tempValues[i] = sensors->getTempCByIndex(i);
      if (tempValues[i]==DEVICE_DISCONNECTED_C) {
        sensors->begin();
        foundSensors = sensors->getDeviceCount();
        LOG_PRINT(F("Devices: "));
        LOG_PRINTLNF(sensors->getDeviceCount(), DEC);
      }
    }
    sensors->requestTemperatures();
  }
}

float TemperatureController::getTempHC() {
  return tempValues[TEMP_SENSOR_INDEX_HC];
}

float TemperatureController::getTempW() {
  return tempValues[TEMP_SENSOR_INDEX_W];
}

float TemperatureController::getTempTank() {
  return tempValues[TEMP_SENSOR_INDEX_TANK];
}

