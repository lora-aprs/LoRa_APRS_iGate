#ifndef TASK_APRS_IS_H_
#define TASK_APRS_IS_H_

#include <APRS-IS.h>
#include <APRSMessage.h>
#include <TaskManager.h>
#include <Timer.h>

class AprsIsTask : public Task {
public:
  explicit AprsIsTask(TaskQueue<std::shared_ptr<APRSMessage>> &toAprsIs);
  virtual ~AprsIsTask();

  virtual bool setup(System &system) override;
  virtual bool loop(System &system) override;

private:
  std::shared_ptr<APRS_IS> _aprs_is;

  TaskQueue<std::shared_ptr<APRSMessage>> &_toAprsIs;

  bool connect(System &system);
};

#endif
