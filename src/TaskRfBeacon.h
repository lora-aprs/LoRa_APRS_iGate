#ifndef TASK_RFBEACON_H_
#define TASK_RFBEACON_H_

#include <TaskManager.h>

class RfBeaconTask : public Task {
public:
  RfBeaconTask();
  virtual ~RfBeaconTask();

  virtual bool setup(System &system) override;
  virtual bool loop(System &system) override;

private:
  //NTPClient _ntpClient;
  bool      _beginCalled;
};

#endif
