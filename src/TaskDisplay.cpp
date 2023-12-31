#include <logger.h>

#include "TaskDisplay.h"
#include "project_configuration.h"

DisplayTask::DisplayTask() : Task("DisplayTask", 0) {
}

DisplayTask::~DisplayTask() {
}

bool DisplayTask::setup(System &system) {
  system.getDisplay().setup();
  if (system.getUserConfig()->display.turn180) {
    system.getDisplay().turn180();
  }
  std::shared_ptr<StatusFrame> statusFrame = std::shared_ptr<StatusFrame>(new StatusFrame(system.getTaskManager().getTasks()));
  system.getDisplay().setStatusFrame(statusFrame);
  if (!system.getUserConfig()->display.alwaysOn) {
    system.getDisplay().activateDisplaySaveMode();
    system.getDisplay().setDisplaySaveTimeout(system.getUserConfig()->display.timeout);
  }
  _stateInfo = system.getUserConfig()->callsign;
  return true;
}

bool DisplayTask::loop(System &system) {
  if (system.getUserConfig()->display.overwritePin != 0 && !digitalRead(system.getUserConfig()->display.overwritePin)) {
    system.getDisplay().activateDistplay();
  }
  system.getDisplay().update();
  return true;
}
