#ifndef TASK_POWER_H_
#define TASK_POWER_H_

#include <APRSMessage.h>
#include <TaskManager.h>
#include <power_management_adc.h>

class PowerTask : public Task {
public:
  PowerTask(TaskQueue<std::shared_ptr<APRSMessage>> &_fromPower);
  virtual ~PowerTask();

  virtual bool setup(System &system) override;
  virtual bool loop(System &system) override;

private:
  PowerManagementADC _powerManagementADC;
  int                _powerReadDelay = 30000;
  unsigned long      _lastTimePowerRead;
  double             _lastVoltage;

  TaskQueue<std::shared_ptr<APRSMessage>> &_fromPower;
};
#endif
