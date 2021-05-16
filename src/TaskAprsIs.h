#ifndef TASK_APRS_IS_H_
#define TASK_APRS_IS_H_

#include <APRS-IS.h>
#include <APRSMessage.h>
#include <TaskManager.h>
#include <Timer.h>

class AprsIsTask : public Task {
public:
  AprsIsTask(TaskQueue<std::shared_ptr<APRSMessage>> & toAprsIs);
  virtual ~AprsIsTask();

  virtual bool setup(std::shared_ptr<System> system) override;
  virtual bool loop(std::shared_ptr<System> system) override;

private:
  std::shared_ptr<APRS_IS> _aprs_is;

  TaskQueue<std::shared_ptr<APRSMessage>> & _toAprsIs;

  bool connect(std::shared_ptr<System> system);
};

#endif
