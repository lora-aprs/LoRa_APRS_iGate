#include <SPIFFS.h>
#include <logger.h>

#include "Task.h"
#include "TaskConfig.h"
#include "configuration.h"

ConfigTask::ConfigTask() : Task(TASK_CONFIG, TaskConfig), _server(80), _config_filename("/is-cfg.json"), _setupDone(false) {
}

ConfigTask::~ConfigTask() {
}

bool ConfigTask::setup(System &system) {
  if (_setupDone) {
    return true;
  }
  fact.addPage(&page);
  fact.loadConfig(_config_filename);

  _html.addPage(&page);
  _html.registerWebServer(_server);
  _server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
  });
  _stateInfo = "waiting";
  _setupDone = true;
  return true;
}

bool ConfigTask::loop(System &system) {
  // we can start the http server just when we are connected to something
  static bool httpServerInitDone = false;
  if (system.isWifiEthConnected() && !httpServerInitDone) {
    _server.begin();
    httpServerInitDone = true;
  }

  if (_html.wasSaved()) {
    fact.saveConfig(_config_filename);
    ESP.restart();
  }

  return true;
}
