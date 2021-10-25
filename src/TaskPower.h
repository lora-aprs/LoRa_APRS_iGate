#ifndef TASK_POWER_H_
#define TASK_POWER_H_

#include <power_management_adc.h>
#include <TaskManager.h>
#include <APRSMessage.h>


class POWERTask : public Task {
public:
  POWERTask(TaskQueue<std::shared_ptr<APRSMessage>> &_fromPower);
  virtual ~POWERTask();

  virtual bool setup(System &system) override;
  virtual bool loop(System &system) override;

private:
  PowerManagementADC _powerManagementADC;
  TaskQueue<std::shared_ptr<APRSMessage>> &_fromPower;
};
#endif
