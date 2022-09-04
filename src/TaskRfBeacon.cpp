#include <logger.h>

#include <TimeLib.h>

#include "Task.h"
#include "TaskRfBeacon.h"
#include "project_configuration.h"

RfBeaconTask::RfBeaconTask() : Task(TASK_RFBEACON, TaskRfBeacon), _beginCalled(false) {
}

RfBeaconTask::~RfBeaconTask() {
}

bool RfBeaconTask::setup(System &system) {
  //_ntpClient.setPoolServerName(system.getUserConfig()->ntpServer.c_str());
  return true;
}

bool RfBeaconTask::loop(System &system) {
  //system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, getName(), "Bin in RfBeaconTask");
  int v=0;
  for (int i=0;i<5;i++){
    v+=analogRead(35);
  }
  double vf=v/5.0/4096.0*3.3;
  //f=v/3;
  system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, getName(), "Wert an Port 35: %f Volt", vf);
  system.beginPacket();
    // Header:
    system.write('<');
    system.write(0xFF);
    system.write(0x01);
    // APRS Data:
    system.write("Just a test");
    system.endPacket();
  delay(500);
  /*
  if (!system.isWifiOrEthConnected()) {
    return false;
  }
  if (!_beginCalled) {
    _ntpClient.begin();
    _beginCalled = true;
  }
  if (_ntpClient.update()) {
    setTime(_ntpClient.getEpochTime());
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, getName(), "Current time: %s", _ntpClient.getFormattedTime().c_str());
  }
  _stateInfo = _ntpClient.getFormattedTime();
  _state     = Okay;
  */
  return true;
}
