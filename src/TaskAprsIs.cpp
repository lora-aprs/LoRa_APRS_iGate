#include <TimeLib.h>
#include <logger.h>

#include "Task.h"
#include "TaskAprsIs.h"
#include "project_configuration.h"

AprsIsTask::AprsIsTask(TaskQueue<std::shared_ptr<APRSMessage>> &toAprsIs) : Task(TASK_APRS_IS, TaskAprsIs), _toAprsIs(toAprsIs) {
}

AprsIsTask::~AprsIsTask() {
}

bool AprsIsTask::setup(System &system) {
  _aprs_is = std::shared_ptr<APRS_IS>(new APRS_IS(system.getUserConfig()->callsign, system.getUserConfig()->aprs_is.passcode, "ESP32-APRS-IS", "0.2"));

  return true;
}

bool AprsIsTask::loop(System &system) {
  if (!system.isWifiEthConnected()) {
    return false;
  }
  if (!_aprs_is->connected()) {
    if (!connect(system)) {
      _stateInfo = "not connected";
      _state     = Error;
      return false;
    }
    _stateInfo = "connected";
    _state     = Okay;
    return false;
  }

  _aprs_is->getAPRSMessage();

  if (!_toAprsIs.empty()) {
    std::shared_ptr<APRSMessage> msg = _toAprsIs.getElement();
    _aprs_is->sendMessage(msg);
  }

  return true;
}

bool AprsIsTask::connect(System &system) {
  logPrintI("connecting to APRS-IS server: ");
  logPrintI(system.getUserConfig()->aprs_is.server);
  logPrintI(" on port: ");
  logPrintlnI(String(system.getUserConfig()->aprs_is.port));
  if (!_aprs_is->connect(system.getUserConfig()->aprs_is.server, system.getUserConfig()->aprs_is.port)) {
    logPrintlnE("Connection failed.");
    return false;
  }
  logPrintlnI("Connected to APRS-IS server!");
  return true;
}
