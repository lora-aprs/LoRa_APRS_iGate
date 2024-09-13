#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_

#include <Arduino.h>
#include <list>
#include <memory>

#include "ConfigurationManagement/configuration.h"
#include "Display/Display.h"

#include "TaskQueue.h"

class System;

enum TaskDisplayState {
  Error,
  Warning,
  Okay,
};

class Task {
public:
  Task(String &name, int taskId) : _state(Okay), _stateInfo("Booting"), _name(name), _taskId(taskId) {
  }
  Task(const char *name, int taskId) : _state(Okay), _stateInfo("Booting"), _name(name), _taskId(taskId) {
  }
  virtual ~Task() {
  }

  String getName() const {
    return _name;
  }
  int getTaskId() const {
    return _taskId;
  }

  TaskDisplayState getState() const {
    return _state;
  }
  String getStateInfo() const {
    return _stateInfo;
  }

  virtual bool setup(System &system) = 0;
  virtual bool loop(System &system)  = 0;

protected:
  TaskDisplayState _state;
  String           _stateInfo;

private:
  String _name;
  int    _taskId;
};

class TaskManager {
public:
  TaskManager();
  ~TaskManager() {
  }

  void              addTask(Task *task);
  void              addAlwaysRunTask(Task *task);
  std::list<Task *> getTasks();

  bool setup(System &system);
  bool loop(System &system);

private:
  std::list<Task *>           _tasks;
  std::list<Task *>::iterator _nextTask;
  std::list<Task *>           _alwaysRunTasks;
};

class StatusFrame : public DisplayFrame {
public:
  explicit StatusFrame(const std::list<Task *> &tasks) : _tasks(tasks) {
  }
  virtual ~StatusFrame() {
  }
  void drawStatusPage(Bitmap &bitmap) override;

private:
  std::list<Task *> _tasks;
};

#include "System.h"

#endif
