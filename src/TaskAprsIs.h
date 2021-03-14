#ifndef TASK_APRS_IS_H_
#define TASK_APRS_IS_H_

#include <APRS-IS.h>
#include <APRSMessage.h>
#include <TaskManager.h>
#include <Timer.h>

class AprsIsTask : public Task {
public:
  AprsIsTask();
  virtual ~AprsIsTask();

  virtual bool setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig) override;
  virtual bool loop(std::shared_ptr<Configuration> config) override;

  TaskQueue<std::shared_ptr<APRSMessage>> inputQueue;

private:
  std::shared_ptr<APRS_IS>     _aprs_is;
  std::shared_ptr<APRSMessage> _beaconMsg;
  Timer                        _beacon_timer;

  bool connect(std::shared_ptr<Configuration> config);
};

#endif
