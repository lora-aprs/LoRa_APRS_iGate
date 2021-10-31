#include <logger.h>

#include "TaskPower.h"
#include "project_configuration.h"

PowerTask::PowerTask(TaskQueue<std::shared_ptr<APRSMessage>> &fromPower) : Task("PowerTask", 0), _fromPower(fromPower) {
}

PowerTask::~PowerTask() {
}

bool PowerTask::setup(System &system) {
  if (!_powerManagementADC.begin(system.getUserConfig()->power.pin, system.getUserConfig()->power.max_voltage, system.getUserConfig()->power.min_voltage)) {
    logPrintlnI("ADC init done!");
    return true;
  }
  logPrintlnE("ADC init failed!");
  return false;
}

bool PowerTask::loop(System &system) {
  if (millis() > _lastTimePowerRead + _powerReadDelay) {
    _lastVoltage = _powerManagementADC.getVoltage();
    logPrintI("Battery: ");
    logPrintlnI(String(_lastVoltage) + " V");
    _stateInfo         = String(_lastVoltage) + " V";
    _lastTimePowerRead = millis();
    system.setVoltage(_lastVoltage);
  }
  _state = Okay;
  return true;
}
