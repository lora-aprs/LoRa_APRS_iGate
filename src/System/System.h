#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <logger.h>
#include <memory>

#include "BoardFinder/BoardFinder.h"
#include "ConfigurationManagement/configuration.h"
#include "Display/Display.h"
#include "TaskManager.h"

class System {
public:
  System();
  ~System();

  void setBoardConfig(BoardConfig const *const boardConfig);
  void setUserConfig(Configuration const *const userConfig);

  BoardConfig const *const   getBoardConfig() const;
  Configuration const *const getUserConfig() const;
  TaskManager               &getTaskManager();
  Display                   &getDisplay();
  bool                       isWifiOrEthConnected() const;
  void                       connectedViaEth(bool status);
  void                       connectedViaWifi(bool status);
  logging::Logger           &getLogger();

private:
  BoardConfig const   *_boardConfig;
  Configuration const *_userConfig;
  TaskManager          _taskManager;
  Display              _display;
  bool                 _isEthConnected;
  bool                 _isWifiConnected;
  logging::Logger      _logger;
};

#endif
