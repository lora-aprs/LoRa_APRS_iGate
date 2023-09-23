#include "TaskManager.h"
#include "Display/FontConfig.h"
#include <logger.h>

#define MODULE_NAME "TaskManager"

TaskManager::TaskManager() {
}

void TaskManager::addTask(Task *task) {
  _tasks.push_back(task);
}

void TaskManager::addAlwaysRunTask(Task *task) {
  _alwaysRunTasks.push_back(task);
}

std::list<Task *> TaskManager::getTasks() {
  std::list<Task *> tasks = _alwaysRunTasks;
  std::copy(_tasks.begin(), _tasks.end(), std::back_inserter(tasks));
  return tasks;
}

bool TaskManager::setup(System &system) {
  system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, MODULE_NAME, "will setup all tasks...");
  for (Task *elem : _alwaysRunTasks) {
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_DEBUG, MODULE_NAME, "call setup for %s", elem->getName().c_str());
    elem->setup(system);
  }
  for (Task *elem : _tasks) {
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_DEBUG, MODULE_NAME, "call setup for %s", elem->getName().c_str());
    elem->setup(system);
  }
  _nextTask = _tasks.begin();
  return true;
}

bool TaskManager::loop(System &system) {
  for (Task *elem : _alwaysRunTasks) {
    elem->loop(system);
  }

  if (_nextTask == _tasks.end()) {
    _nextTask = _tasks.begin();
  }
  bool ret = (*_nextTask)->loop(system);
  ++_nextTask;
  return ret;
}

// cppcheck-suppress unusedFunction
void StatusFrame::drawStatusPage(Bitmap &bitmap) {
  int y = 0;
  for (Task const *const task : _tasks) {
    int x = bitmap.drawString(0, y, (task->getName()).substring(0, task->getName().indexOf("Task")));
    x     = bitmap.drawString(x, y, ": ");
    if (task->getStateInfo() == "") {
      switch (task->getState()) {
      case Error:
        bitmap.drawString(x, y, "Error");
        break;
      case Warning:
        bitmap.drawString(x, y, "Warning");
      default:
        break;
      }
      bitmap.drawString(x, y, "Okay");
    } else {
      bitmap.drawString(x, y, task->getStateInfo());
    }
    y += getSystemFont()->heightInPixel;
  }
}
