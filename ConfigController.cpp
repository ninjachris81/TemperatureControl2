#include "ConfigController.h"

#include <LogHelper.h>

ConfigController::ConfigController() : AbstractTriggerTask() {
}

void ConfigController::init() {
  loadConfig();
}

void ConfigController::update() {  
}

ConfigController::ConfigStruct* ConfigController::getConfig() {
  return &settings;
}

void ConfigController::loadConfig() {
  LOG_PRINTLN(F("Loading config"));

  // To make sure there are settings, and they are YOURS!
  // If nothing is found it will use the default settings.
  if (//EEPROM.read(CONFIG_START + sizeof(settings) - 1) == settings.version_of_program[3] // this is '\0'
      EEPROM.read(CONFIG_START + sizeof(settings) - 2) == settings.version_of_program[2] &&
      EEPROM.read(CONFIG_START + sizeof(settings) - 3) == settings.version_of_program[1] &&
      EEPROM.read(CONFIG_START + sizeof(settings) - 4) == settings.version_of_program[0])
  { // reads settings from EEPROM
    for (unsigned int t=0; t<sizeof(settings); t++)
      *((char*)&settings + t) = EEPROM.read(CONFIG_START + t);
  } else {
    // settings aren't valid! will overwrite with default settings
    saveConfig();
  }
}

void ConfigController::saveConfig() {
  LOG_PRINTLN(F("Saving config"));
  
  for (unsigned int t=0; t<sizeof(settings); t++)
  { // writes to EEPROM
    EEPROM.write(CONFIG_START + t, *((char*)&settings + t));
    // and verifies the data
    if (EEPROM.read(CONFIG_START + t) != *((char*)&settings + t))
    {
      // error writing to EEPROM
    }
  }
}
