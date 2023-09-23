#ifndef TASK_OTA_H_
#define TASK_OTA_H_

#include "System/TaskManager.h"
#include <ArduinoOTA.h>

class OTATask : public Task {
public:
  OTATask();
  virtual ~OTATask();

  virtual bool setup(System &system) override;
  virtual bool loop(System &system) override;

private:
  ArduinoOTAClass _ota;
  bool            _beginCalled;
};

#endif
