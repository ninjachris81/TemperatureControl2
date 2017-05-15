#ifndef SERVERCONTROLLER_H
#define SERVERCONTROLLER_H

#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <AbstractTask.h>

#define SERVER_PORT 80

class ServerController : public AbstractTask {
public:
  ServerController();
  ~ServerController();

  void init();

  void update();

  TaskManager* getTaskManager();

  static ServerController* getInstance();
  
private:
  static ServerController* instance;
  static ESP8266WebServer *server;

  static void handleNotFound();
  static void handleStatus();

};

#endif    // SERVERCONTROLLER_H
