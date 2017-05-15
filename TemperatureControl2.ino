/* META INFOS
target_package=esp8266
target_platform=esp8266
board=d1_mini
*/
#include <LogHelper.h>
#include <AbstractIntervalTask.h>
#include <AbstractTask.h>
#include <AbstractTriggerTask.h>
#include <TaskManager.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "Credentials.h"
#include "IOController.h"
#include "ServerController.h"
#include "TimeController.h"
#include "TemperatureController.h"

TaskManager taskManager;

IOController ioController;
ServerController serverController;
TimeController timeController;
TemperatureController temperatureController;

void setupOTA() {
  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword((const char *)"123");

  ArduinoOTA.onStart([]() {
    LOG_PRINTLN(F("Start"));
  });
  ArduinoOTA.onEnd([]() {
    LOG_PRINTLN(F("End"));
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    //LOG_PRINTLNF(F("Progress: %u%%\r"), (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    //LOG_PRINTLNF(F("Error[%u]: "), error);
    if (error == OTA_AUTH_ERROR) LOG_PRINTLN(F("Auth Failed"));
    else if (error == OTA_BEGIN_ERROR) LOG_PRINTLN(F("Begin Failed"));
    else if (error == OTA_CONNECT_ERROR) LOG_PRINTLN(F("Connect Failed"));
    else if (error == OTA_RECEIVE_ERROR) LOG_PRINTLN(F("Receive Failed"));
    else if (error == OTA_END_ERROR) LOG_PRINTLN(F("End Failed"));
  });
  ArduinoOTA.begin();
}

void setup() {
  LOG_INIT();

  LOG_PRINTLN(F("INIT"));

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    LOG_PRINTLN(F("Connection Failed! Rebooting..."));
    delay(5000);
    ESP.restart();
  }
  LOG_PRINTLN(F("Wifi connected"));

  setupOTA();

  taskManager.registerTask(&ioController);
  taskManager.registerTask(&serverController);
  taskManager.registerTask(&timeController);
  taskManager.registerTask(&temperatureController);
  
  taskManager.init();
}

void loop() {
  taskManager.update();
  delay(100);
  ArduinoOTA.handle();
}
