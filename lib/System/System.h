#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <memory>

#include "TaskManager.h"
#include <BoardFinder.h>
#include <Display.h>
#include <power_management_adc.h>
#include <configuration.h>

class System {
public:
  System();
  ~System();

  void setBoardConfig(BoardConfig const *const boardConfig);
  void setUserConfig(Configuration const *const userConfig);

  BoardConfig const *const   getBoardConfig() const;
  Configuration const *const getUserConfig() const;
  TaskManager &              getTaskManager();
  Display &                  getDisplay();
  PowerManagementADC &       getPower();
  bool                       isWifiEthConnected() const;
  void                       connectedViaWifiEth(bool status);

private:
  BoardConfig const *  _boardConfig;
  Configuration const *_userConfig;
  TaskManager          _taskManager;
  Display              _display;
  PowerManagementADC   _powerManagementADC;
  bool                 _isWifiEthConnected;
};

#endif
