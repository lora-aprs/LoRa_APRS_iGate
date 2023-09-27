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

  bool begin(TwoWire &port);

  void activateLoRa();
  void deactivateLoRa();

  void activateGPS();
  void deactivateGPS();

  void activateOLED();
  void deactivateOLED();

  void enableChgLed();
  void disableChgLed();

  void activateMeasurement();
  void deactivateMeasurement();

  double getBatteryVoltage();
  double getBatteryChargeDischargeCurrent();

  bool isBatteryConnect();
  bool isCharging();
};

class AXP2101 : public PowerManagement {
public:
  AXP2101();

  bool begin(TwoWire &port);

  void activateLoRa();
  void deactivateLoRa();

  void activateGPS();
  void deactivateGPS();

  void activateOLED();
  void deactivateOLED();

  void enableChgLed();
  void disableChgLed();

  void activateMeasurement();
  void deactivateMeasurement();

  double getBatteryVoltage();
  double getBatteryChargeDischargeCurrent();

  bool isBatteryConnect();
  bool isCharging();
};

#endif
