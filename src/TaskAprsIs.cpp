#include <logger.h>

#include "Task.h"
#include "TaskAprsIs.h"
#include "project_configuration.h"

AprsIsTask::AprsIsTask(TaskQueue<std::shared_ptr<APRSMessage>> &toAprsIs, TaskQueue<std::shared_ptr<APRSMessage>> &toModem) : Task(TASK_APRS_IS, TaskAprsIs), _toAprsIs(toAprsIs), _toModem(toModem) {
}

AprsIsTask::~AprsIsTask() {
}

bool AprsIsTask::setup(System &system) {
  _aprs_is.setup(system.getUserConfig()->callsign, system.getUserConfig()->aprs_is.passcode, "ESP32-APRS-IS", "0.2");
  return true;
}

bool AprsIsTask::loop(System &system) {
  if (!system.isWifiOrEthConnected()) {
    return false;
  }
  if (!_aprs_is.connected()) {
    if (!connect(system)) {
      _stateInfo = "not connected";
      _state     = Error;
      return false;
    }
    _stateInfo = "connected";
    _state     = Okay;
    return false;
  }

  std::shared_ptr<APRSMessage> msg = _aprs_is.getAPRSMessage();
  if (msg) {
    _toModem.addElement(msg);
  }

  if (!_toAprsIs.empty()) {
    std::shared_ptr<APRSMessage> msg = _toAprsIs.getElement();
    _aprs_is.sendMessage(msg);
  }

  return true;
}

bool AprsIsTask::connect(System &system) {
  system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, getName(), "connecting to APRS-IS server: %s on port: %d, with filter: '%s'", system.getUserConfig()->aprs_is.server.c_str(), system.getUserConfig()->aprs_is.port, system.getUserConfig()->aprs_is.filter);
  APRS_IS::ConnectionStatus status = APRS_IS::ConnectionStatus::ERROR_CONNECTION;
  if (system.getUserConfig()->aprs_is.filter.isEmpty()) {
    status = _aprs_is.connect(system.getUserConfig()->aprs_is.server, system.getUserConfig()->aprs_is.port);
  } else {
    status = _aprs_is.connect(system.getUserConfig()->aprs_is.server, system.getUserConfig()->aprs_is.port, system.getUserConfig()->aprs_is.filter);
  }
  if (status == APRS_IS::ERROR_CONNECTION) {
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "Something went wrong on connecting! Is the server reachable?");
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "Connection failed.");
    return false;
  } else if (status == APRS_IS::ERROR_PASSCODE) {
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "User can not be verified with passcode!");
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "Connection failed.");
    return false;
  }
  system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, getName(), "Connected to APRS-IS server!");
  return true;
}
