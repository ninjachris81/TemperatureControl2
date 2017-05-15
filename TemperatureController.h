#ifndef TEMPERATURECONTROLLER_H
#define TEMPERATURECONTROLLER_H

#include <AbstractIntervalTask.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "Pins.h"

#define TEMP_INTERVAL_MS 1000

#define SENSOR_COUNT 3

#define TEMP_SENSOR_INDEX_HC 0
#define TEMP_SENSOR_INDEX_W 1
#define TEMP_SENSOR_INDEX_TANK 2

class TemperatureController : public AbstractIntervalTask {
public:
  TemperatureController();
  ~TemperatureController();

  void init();

  void update();

  float getTempHC();
  float getTempW();
  float getTempTank();

private:
  uint8_t foundSensors = 0;
  OneWire *oneWire;
  DallasTemperature* sensors;
  float tempValues[SENSOR_COUNT];
};

#endif    // TEMPERATURECONTROLLER_H
