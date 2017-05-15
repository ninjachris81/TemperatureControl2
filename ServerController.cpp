#include "ServerController.h"
#include <ESP8266WiFi.h>
#include <LogHelper.h>
#include <Time.h>
#include <TimeLib.h>

#include "TemperatureController.h"
#include "TaskIDs.h"

ESP8266WebServer* ServerController::server = NULL;
ServerController* ServerController::instance = NULL;

ServerController::ServerController() : AbstractTask() {
  if (server==NULL) {
    LOG_PRINTLN(F("Creating new web server"));
    server = new ESP8266WebServer(SERVER_PORT);
  }
  if (instance==NULL) {
    instance = this;
  }
}

ServerController::~ServerController() {
  server->stop();
  delete server;
}

void ServerController::init() {
  server->onNotFound(ServerController::handleNotFound);

  server->on("/status", ServerController::handleStatus);

  server->begin();
}

void ServerController::update() {
  server->handleClient();
}

TaskManager* ServerController::getTaskManager() {
  return taskManager;
}

ServerController* ServerController::getInstance() {
  return instance;
}

void ServerController::handleNotFound() {
  server->send ( 404, "text/plain", "Not Found" );
}

void ServerController::handleStatus() {
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["ut"] = millis();
  root["t"] = now();
  root["rssi"] = WiFi.RSSI();
  root["fh"] = ESP.getFreeHeap();
  root["thc"] = getInstance()->getTaskManager()->getTask<TemperatureController*>(TEMPERATURE_CONTROLLER)->getTempHC();
  root["tw"] = getInstance()->getTaskManager()->getTask<TemperatureController*>(TEMPERATURE_CONTROLLER)->getTempW();
  root["tt"] = getInstance()->getTaskManager()->getTask<TemperatureController*>(TEMPERATURE_CONTROLLER)->getTempTank();

  String tmpStr;
  root.printTo(tmpStr);
  server->send ( 200, "application/json", tmpStr);
}
