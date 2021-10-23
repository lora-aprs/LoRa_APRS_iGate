#include <logger.h>

#include "TaskPower.h"
#include "project_configuration.h"

POWERTask::POWERTask() : Task("POWERTask", 0) {
}

POWERTask::~POWERTask() {
}

bool POWERTask::setup(System &system) {
  if (!_powerManagementADC.begin(system.getUserConfig()->power.pin, system.getUserConfig()->power.max_voltage, system.getUserConfig()->power.min_voltage)) {
    logPrintlnI("ADC init done!");
    return true;
  }
  logPrintlnE("ADC init failed!");
  return false;
}

bool POWERTask::loop(System &system) {
  logPrintI("Voltage: ");
  logPrintlnI(String(_powerManagementADC.getVoltage()));
  // _stateInfo = "voltage " + String(_powerManagementADC.getVoltage());
  _state     = Okay;
  return true;
}
