#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <memory>

#include "TaskManager.h"
#include <BoardFinder.h>
#include <Display.h>
#include <configuration.h>

class System {
public:
  System(std::shared_ptr<BoardConfig> boardConfig, std::shared_ptr<Configuration> userConfig);
  ~System();

  std::shared_ptr<BoardConfig>   getBoardConfig() const;
  std::shared_ptr<Configuration> getUserConfig() const;
  TaskManager &                  getTaskManager();
  Display &                      getDisplay();

private:
  std::shared_ptr<BoardConfig>   _boardConfig;
  std::shared_ptr<Configuration> _userConfig;
  TaskManager                    _taskManager;
  Display                        _display;
};

#endif
