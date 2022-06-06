#include <logger.h>

#include "Task.h"
#include "TaskOTA.h"
#include "project_configuration.h"

OTATask::OTATask() : Task(TASK_OTA, TaskOta), _beginCalled(false) {
}

OTATask::~OTATask() {
}

bool OTATask::setup(System &system) {
  _ota.onStart([&]() {
        String type;
        if (_ota.getCommand() == U_FLASH) {
          type = "sketch";
        } else { // U_SPIFFS
          type = "filesystem";
        }
        system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, getName(), "Start updating %s. please wait, this prozess is taking some time!", type.c_str());
      })
      .onEnd([&]() {
        system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, getName(), "OTA End");
      })
      .onError([&](ota_error_t error) {
        String error_str;
        if (error == OTA_AUTH_ERROR) {
          error_str = "Auth Failed";
        } else if (error == OTA_BEGIN_ERROR) {
          error_str = "Begin Failed";
        } else if (error == OTA_CONNECT_ERROR) {
          error_str = "Connect Failed";
        } else if (error == OTA_RECEIVE_ERROR) {
          error_str = "Receive Failed";
        } else if (error == OTA_END_ERROR) {
          error_str = "End Failed";
        }
        system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "Error[%d]: %s", error, error_str.c_str());
      });
  if (system.getUserConfig()->network.hostname.overwrite) {
    _ota.setHostname(system.getUserConfig()->network.hostname.name.c_str());
  } else {
    _ota.setHostname(system.getUserConfig()->callsign.c_str());
  }
  _stateInfo = "";
  return true;
}

bool OTATask::loop(System &system) {
  if (!_beginCalled) {
    _ota.begin();
    _beginCalled = true;
  }
  _ota.handle();
  return true;
}
