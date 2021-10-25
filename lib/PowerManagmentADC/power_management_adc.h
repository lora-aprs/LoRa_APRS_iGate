#ifndef POWER_MANAGEMENT_ADC_H_
#define POWER_MANAGEMENT_ADC_H_

#include <Arduino.h>
#include <ESP32AnalogRead.h>

class PowerManagementADC {
public:
  PowerManagementADC();
  ~PowerManagementADC();

  bool begin(int pin, double max, double min);
  double getVoltage();

private:
  ESP32AnalogRead adc;
  unsigned long _updateInterval = 60000;  // In ms
  int _pin;
  double  _max_voltage;
  double  _min_voltage;
};

#endif

