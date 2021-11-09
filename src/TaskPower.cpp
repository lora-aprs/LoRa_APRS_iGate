#include <logger.h>

#include "TaskPower.h"
#include "project_configuration.h"
#include <TimeLib.h>

PowerTask::PowerTask(TaskQueue<std::shared_ptr<APRSExtMessage>> &fromPower) : Task("PowerTask", 0), _fromPower(fromPower) {
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
    logPrintlnI(timeString(now()) + " (UTC), ");
    logPrintI("Battery: ");
    logPrintlnI(String(_lastVoltage) + " V");
    //logPrintlnI("Free Heap         : " + String(esp_get_free_heap_size()));
    logPrintlnI("Free Minimum Heap : " + String(esp_get_minimum_free_heap_size()));
    //logPrintlnI("Free Internal Heap: " + String(esp_get_free_internal_heap_size()));
    _stateInfo         = String(_lastVoltage) + " V";
    _lastTimePowerRead = millis();
    system.setVoltage(_lastVoltage);
  }
  _state = Okay;
  return true;
}
