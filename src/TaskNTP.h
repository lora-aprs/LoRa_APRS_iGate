#ifndef TASK_NTP_H_
#define TASK_NTP_H_

#include "NTPClient/NTPClient.h"
#include "System/TaskManager.h"

class NTPTask : public Task {
public:
  NTPTask();
  virtual ~NTPTask();

  virtual bool setup(System &system) override;
  virtual bool loop(System &system) override;

private:
  NTPClient _ntpClient;
  bool      _beginCalled;
};

#endif
