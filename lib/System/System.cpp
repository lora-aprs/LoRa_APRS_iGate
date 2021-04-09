
#include "System.h"

System::System(std::shared_ptr<BoardConfig> boardConfig, std::shared_ptr<Configuration> userConfig) : _boardConfig(boardConfig), _userConfig(userConfig), _isWifiEthConnected(false) {
}

System::~System() {
}

std::shared_ptr<BoardConfig> System::getBoardConfig() const {
  return _boardConfig;
}

std::shared_ptr<Configuration> System::getUserConfig() const {
  return _userConfig;
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
