#include <logger.h>
#include "power_management_adc.h"


PowerManagementADC::PowerManagementADC() {
}

PowerManagementADC::~PowerManagementADC() {
}

// cppcheck-suppress unusedFunction
bool PowerManagementADC::begin(int pin, double max, double min) {
	adc.attach(pin);
  _pin = pin;
  _max_voltage = max;
  _min_voltage = min;
  if (adc.readVoltage() > 0.0) return false;
  return true;
}


// cppcheck-suppress unusedFunction
double PowerManagementADC::getVoltage() {
  _last_voltage = adc.readVoltage() * _scale;
  logPrintlnI("getVoltage() " + String(_last_voltage));
  return _last_voltage;
}

