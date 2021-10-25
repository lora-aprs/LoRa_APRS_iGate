#include <logger.h>

#include "TaskPower.h"
#include "project_configuration.h"

POWERTask::POWERTask(TaskQueue<std::shared_ptr<APRSMessage>> &fromPower) : Task("POWERTask", 0),  _fromPower(fromPower) {
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
  // logPrintI("Voltage: ");
  // logPrintlnI(String(_powerManagementADC.getVoltage()));
  _stateInfo = String(_powerManagementADC.getVoltage()*2.0) + "V";
  _state     = Okay;
  return true;
}
