#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <memory>

#include "TaskManager.h"
#include <BoardFinder.h>
#include <Display.h>

class Configuration; // needs to be defined in user programm

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
  bool                       isWifiEthConnected() const;
  void                       connectedViaWifiEth(bool status);

private:
  BoardConfig const *  _boardConfig;
  Configuration const *_userConfig;
  TaskManager          _taskManager;
  Display              _display;
  bool                 _isWifiEthConnected;
};

#endif
