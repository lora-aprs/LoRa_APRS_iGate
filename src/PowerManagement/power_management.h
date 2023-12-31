#ifndef POWER_MANAGEMENT_H_
#define POWER_MANAGEMENT_H_

#include <Wire.h>
#include <XPowersLibInterface.hpp>

class PowerManagement {
public:
  ~PowerManagement() {
  }

  virtual bool begin(TwoWire &port) = 0;

  virtual void activateLoRa()   = 0;
  virtual void deactivateLoRa() = 0;

  virtual void activateGPS()   = 0;
  virtual void deactivateGPS() = 0;

  virtual void activateOLED()   = 0;
  virtual void deactivateOLED() = 0;

  virtual void activateMeasurement()   = 0;
  virtual void deactivateMeasurement() = 0;

  virtual double getBatteryVoltage() = 0;

  virtual double getBatteryChargeDischargeCurrent() = 0;

  virtual bool isBatteryConnect() = 0;
  virtual bool isCharging()       = 0;

protected:
  XPowersLibInterface *_pmu = 0;
};

class AXP192 : public PowerManagement {
public:
  AXP192();

  bool begin(TwoWire &port) override;

  void activateLoRa() override;
  void deactivateLoRa() override;

  void activateGPS() override;
  void deactivateGPS() override;

  void activateOLED() override;
  void deactivateOLED() override;

  void activateMeasurement() override;
  void deactivateMeasurement() override;

  double getBatteryVoltage() override;
  double getBatteryChargeDischargeCurrent() override;

  bool isBatteryConnect() override;
  bool isCharging() override;
};

class AXP2101 : public PowerManagement {
public:
  AXP2101();

  bool begin(TwoWire &port) override;

  void activateLoRa() override;
  void deactivateLoRa() override;

  void activateGPS() override;
  void deactivateGPS() override;

  void activateOLED() override;
  void deactivateOLED() override;

  void activateMeasurement() override;
  void deactivateMeasurement() override;

  double getBatteryVoltage() override;
  double getBatteryChargeDischargeCurrent() override;

  bool isBatteryConnect() override;
  bool isCharging() override;
};

#endif
