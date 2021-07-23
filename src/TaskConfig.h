#ifndef TASK_CONFIG_H_
#define TASK_CONFIG_H_

#include "configuration.h"
#include <TaskManager.h>

class ConfigTask : public Task {
public:
  ConfigTask();
  virtual ~ConfigTask();

  virtual bool setup(System &system) override;
  virtual bool loop(System &system) override;

  ConfigFactory fact;

private:
  ConfigHTML     _html;
  AsyncWebServer _server;
  const String   _config_filename;
  bool           _setupDone;
};

#endif
