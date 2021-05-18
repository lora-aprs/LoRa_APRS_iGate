#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <memory>

#include "TaskManager.h"
#include <BoardFinder.h>
#include <Display.h>
#include <configuration.h>

class System {
public:
  System(BoardConfig const *const boardConfig, std::shared_ptr<Configuration> userConfig);
  ~System();

  BoardConfig const *const       getBoardConfig() const;
  std::shared_ptr<Configuration> getUserConfig() const;
  TaskManager &                  getTaskManager();
  Display &                      getDisplay();
  bool                           isWifiEthConnected() const;
  void                           connectedViaWifiEth(bool status);

private:
  BoardConfig const *const       _boardConfig;
  std::shared_ptr<Configuration> _userConfig;
  TaskManager                    _taskManager;
  Display                        _display;
  bool                           _isWifiEthConnected;
};

#endif
