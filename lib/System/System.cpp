
#include "System.h"

System::System() : _boardConfig(0), _userConfig(0), _dataConfig(0), _isWifiEthConnected(false) {
}

System::~System() {
}

void System::setBoardConfig(BoardConfig const *const boardConfig) {
  _boardConfig = boardConfig;
}

void System::setUserConfig(Configuration const *const userConfig) {
  _userConfig = userConfig;
}

BoardConfig const *const System::getBoardConfig() const {
  return _boardConfig;
}

Configuration const *const System::getUserConfig() const {
  return _userConfig;
}

DynamicJsonDocument const *const System::getDataConfig() const {
  return _dataConfig;
}

TaskManager &System::getTaskManager() {
  return _taskManager;
}

Display &System::getDisplay() {
  return _display;
}

bool System::isWifiEthConnected() const {
  return _isWifiEthConnected;
}

void System::connectedViaWifiEth(bool status) {
  _isWifiEthConnected = status;
}

double System::getVoltage() {
  return _voltage;
}

void System::setVoltage(double last_voltage) {
  _voltage = last_voltage;
}

void System::setCopyToTelegram() {
  _copyToTelegram = true;
};

void System::unsetCopyToTelegram() {
  _copyToTelegram = false;
};

bool System::isCopyToTelegram() const {
  return _copyToTelegram;
};
