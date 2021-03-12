#ifndef TASK_OTA_H_
#define TASK_OTA_H_

#include <ArduinoOTA.h>
#include <TaskManager.h>

class OTATask : public Task {
public:
  OTATask();
  virtual ~OTATask();

  virtual bool setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig) override;
  virtual bool loop(std::shared_ptr<Configuration> config) override;

private:
  std::shared_ptr<ArduinoOTAClass> _ota;
  bool                             _beginCalled;
};

#endif
