#include <TimeLib.h>
#include <logger.h>

#include "TaskDisplay.h"
#include "project_configuration.h"

DisplayTask::DisplayTask() : Task("DisplayTask", 0) {
}

DisplayTask::~DisplayTask() {
}

bool DisplayTask::setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig) {
  Display::instance().setup(boardConfig);
  if (config->display.turn180) {
    Display::instance().turn180();
  }
  std::shared_ptr<StatusFrame> statusFrame = std::shared_ptr<StatusFrame>(new StatusFrame(TaskManager::instance().getTasks()));
  Display::instance().setStatusFrame(statusFrame);
  if (!config->display.alwaysOn) {
    Display::instance().activateDisplaySaveMode();
    Display::instance().setDisplayTimeout(config->display.timeout);
  }
  _stateInfo = config->callsign;
  return true;
}

bool DisplayTask::loop(std::shared_ptr<Configuration> config) {
  Display::instance().update();
  return true;
}
