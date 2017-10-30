#include "CommController.h"
#include <LogHelper.h>
#include <Time.h>
#include <TimeLib.h>

#include "Pins.h"
#include "TimeHelper.h"
#include "SerialProtocol.h"
#include "IOController.h"
#include "TaskIDs.h"

CommController::CommController() : AbstractTask() {
  
}

void CommController::init() {
  PIN_SERIAL_COMM.begin(9600);
}

void CommController::update() {
  if (PIN_SERIAL_COMM.available()) {
    String s = PIN_SERIAL_COMM.readStringUntil('\n');

    LOG_PRINTLN(F("Received:"));
    LOG_PRINTLN(s);

    uint8_t cmd = s.substring(0,2).toInt();

    switch(cmd) {
        case CMD_TIME: {
          unsigned long epoch = strtoul(s.substring(2).c_str(), NULL, 10);
          TimeHelper::setTime(epoch);
          break;
        }
        case CMD_SOLAR_PUMP:
        case CMD_RADIATOR_PUMP:
        case CMD_GAS_BURNER:
        case CMD_CIRCULATION_PUMP:
        case CMD_HEAT_CHANGER_PUMP:
          taskManager->getTask<IOController*>(IO_CONTROLLER)->setState(IO_PIN_BASE - cmd, s.substring(2).toInt()==1);
          break;
      default:
        LOG_PRINT(F("Unknown cmd "));
        LOG_PRINTLN(cmd);
    }
  }
}

