#include <XPowersAXP192.tpp>
#include <XPowersAXP2101.tpp>

#include "power_management.h"

AXP192::AXP192() {
}

// cppcheck-suppress unusedFunction
bool AXP192::begin(TwoWire &port) {
  _pmu = new XPowersAXP192(port);
  if (!_pmu->init()) {
    delete _pmu;
    _pmu = 0;
    return false;
  }

  // lora radio power channel
  _pmu->setPowerChannelVoltage(XPOWERS_LDO2, 3300);

  // oled module power channel,
  // disable it will cause abnormal communication between boot and AXP power supply,
  // do not turn it off
  _pmu->setPowerChannelVoltage(XPOWERS_DCDC1, 3300);

  // gnss module power channel -  now turned on in setGpsPower
  _pmu->setPowerChannelVoltage(XPOWERS_LDO3, 3300);

  // protected oled power source
  //_pmu->setProtectedChannel(XPOWERS_DCDC1);
  // protected esp32 power source
  _pmu->setProtectedChannel(XPOWERS_DCDC3);

  // disable not use channel
  _pmu->disablePowerOutput(XPOWERS_DCDC2);

  // disable all axp chip interrupt
  _pmu->disableIRQ(XPOWERS_AXP192_ALL_IRQ);

  // Set constant current charging current
  _pmu->setChargerConstantCurr(XPOWERS_AXP192_CHG_CUR_780MA);

  // Set up the charging voltage
  _pmu->setChargeTargetVoltage(XPOWERS_AXP192_CHG_VOL_4V2);

  _pmu->setChargingLedMode(XPOWERS_CHG_LED_CTRL_CHG);

  return true;
}

// cppcheck-suppress unusedFunction
void AXP192::activateLoRa() {
  _pmu->enablePowerOutput(XPOWERS_LDO2);
}

// cppcheck-suppress unusedFunction
void AXP192::deactivateLoRa() {
  _pmu->disablePowerOutput(XPOWERS_LDO2);
}

// cppcheck-suppress unusedFunction
void AXP192::activateGPS() {
  _pmu->enablePowerOutput(XPOWERS_LDO3);
}

// cppcheck-suppress unusedFunction
void AXP192::deactivateGPS() {
  _pmu->disablePowerOutput(XPOWERS_LDO3);
}

// cppcheck-suppress unusedFunction
void AXP192::activateOLED() {
  _pmu->enablePowerOutput(XPOWERS_DCDC1);
}

// cppcheck-suppress unusedFunction
void AXP192::deactivateOLED() {
  _pmu->disablePowerOutput(XPOWERS_DCDC1);
}

// cppcheck-suppress unusedFunction
void AXP192::activateMeasurement() {
  _pmu->enableBattVoltageMeasure();
}

// cppcheck-suppress unusedFunction
void AXP192::deactivateMeasurement() {
  _pmu->disableBattVoltageMeasure();
}

// cppcheck-suppress unusedFunction
double AXP192::getBatteryVoltage() {
  return _pmu->getBattVoltage() / 1000.0;
}

// cppcheck-suppress unusedFunction
double AXP192::getBatteryChargeDischargeCurrent() {
  if (isCharging()) {
    return static_cast<XPowersAXP192 *>(_pmu)->getBatteryChargeCurrent();
  }
  return -1.0 * static_cast<XPowersAXP192 *>(_pmu)->getBattDischargeCurrent();
}

bool AXP192::isBatteryConnect() {
  return _pmu->isBatteryConnect();
}

bool AXP192::isCharging() {
  return _pmu->isCharging();
}

AXP2101::AXP2101() {
}

// cppcheck-suppress unusedFunction
bool AXP2101::begin(TwoWire &port) {
  _pmu = new XPowersAXP2101(port);
  if (!_pmu->init()) {
    delete _pmu;
    _pmu = 0;
    return false;
  }

  // Unuse power channel
  _pmu->disablePowerOutput(XPOWERS_DCDC2);
  _pmu->disablePowerOutput(XPOWERS_DCDC3);
  _pmu->disablePowerOutput(XPOWERS_DCDC4);
  _pmu->disablePowerOutput(XPOWERS_DCDC5);
  _pmu->disablePowerOutput(XPOWERS_ALDO1);
  _pmu->disablePowerOutput(XPOWERS_ALDO4);
  _pmu->disablePowerOutput(XPOWERS_BLDO1);
  _pmu->disablePowerOutput(XPOWERS_BLDO2);
  _pmu->disablePowerOutput(XPOWERS_DLDO1);
  _pmu->disablePowerOutput(XPOWERS_DLDO2);

  // GNSS RTC PowerVDD 3300mV
  _pmu->setPowerChannelVoltage(XPOWERS_VBACKUP, 3300);
  _pmu->enablePowerOutput(XPOWERS_VBACKUP);

  // LoRa VDD 3300mV
  _pmu->setPowerChannelVoltage(XPOWERS_ALDO2, 3300);
  _pmu->enablePowerOutput(XPOWERS_ALDO2);

  // GNSS VDD 3300mV
  _pmu->setPowerChannelVoltage(XPOWERS_ALDO3, 3300);
  _pmu->enablePowerOutput(XPOWERS_ALDO3);

  // disable all axp chip interrupt
  _pmu->disableIRQ(XPOWERS_AXP2101_ALL_IRQ);

  // Set constant current charging current
  _pmu->setChargerConstantCurr(XPOWERS_AXP2101_CHG_CUR_800MA);

  // Set up the charging voltage
  _pmu->setChargeTargetVoltage(XPOWERS_AXP2101_CHG_VOL_4V2);

  _pmu->setChargingLedMode(XPOWERS_CHG_LED_CTRL_CHG);

  return true;
}

// cppcheck-suppress unusedFunction
void AXP2101::activateLoRa() {
  _pmu->enablePowerOutput(XPOWERS_ALDO2);
}

// cppcheck-suppress unusedFunction
void AXP2101::deactivateLoRa() {
  _pmu->disablePowerOutput(XPOWERS_ALDO2);
}

// cppcheck-suppress unusedFunction
void AXP2101::activateGPS() {
  _pmu->enablePowerOutput(XPOWERS_ALDO3);
}

// cppcheck-suppress unusedFunction
void AXP2101::deactivateGPS() {
  _pmu->disablePowerOutput(XPOWERS_ALDO3);
}

// cppcheck-suppress unusedFunction
void AXP2101::activateOLED() {
  _pmu->enablePowerOutput(XPOWERS_DCDC1);
}

// cppcheck-suppress unusedFunction
void AXP2101::deactivateOLED() {
  _pmu->disablePowerOutput(XPOWERS_DCDC1);
}

// cppcheck-suppress unusedFunction
void AXP2101::activateMeasurement() {
  _pmu->enableBattVoltageMeasure();
}

// cppcheck-suppress unusedFunction
void AXP2101::deactivateMeasurement() {
  _pmu->disableBattVoltageMeasure();
}

// cppcheck-suppress unusedFunction
double AXP2101::getBatteryVoltage() {
  return _pmu->getBattVoltage() / 1000.0;
}

// cppcheck-suppress unusedFunction
double AXP2101::getBatteryChargeDischargeCurrent() {
  return 0.0;
}

bool AXP2101::isBatteryConnect() {
  return _pmu->isBatteryConnect();
}

bool AXP2101::isCharging() {
  return _pmu->isCharging();
}
