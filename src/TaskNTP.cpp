#include <TimeLib.h>
#include <logger.h>

#include "Task.h"
#include "TaskNTP.h"
#include "project_configuration.h"

NTPTask::NTPTask() : Task(TASK_NTP, TaskNtp), _beginCalled(false) {
}

NTPTask::~NTPTask() {
}

bool NTPTask::setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig) {
  _ntpClient = std::shared_ptr<NTPClient>(new NTPClient(config->ntpServer.c_str()));
  return true;
}

bool NTPTask::loop(std::shared_ptr<Configuration> config) {
  if (!_beginCalled) {
    _ntpClient->begin();
    _beginCalled = true;
  }
  if (_ntpClient->update()) {
    setTime(_ntpClient->getEpochTime());
    logPrintI("Current time: ");
    logPrintlnI(_ntpClient->getFormattedTime());
  }
  _stateInfo = _ntpClient->getFormattedTime();
  _state     = Okay;
  return true;
}
