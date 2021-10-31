#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <memory>

#include "TaskManager.h"
#include <BoardFinder.h>
#include <Display.h>
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
  bool                       isWifiEthConnected() const;
  bool                       isCopyToTelegram() const;
  void                       setCopyToTelegram();
  void                       unsetCopyToTelegram();
  void                       connectedViaWifiEth(bool status);
  double                     getVoltage();
  void                       setVoltage(double last_voltage);

private:
  BoardConfig const *  _boardConfig;
  Configuration const *_userConfig;
  TaskManager          _taskManager;
  Display              _display;
  bool                 _isWifiEthConnected;
  bool                 _copyToTelegram = false;
  double               _voltage        = -1.0;
};

#endif
