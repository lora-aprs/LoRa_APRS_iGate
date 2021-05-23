#ifndef TASK_ETH_H_
#define TASK_ETH_H_

#include <TaskManager.h>

void WiFiEvent(WiFiEvent_t event);

class EthTask : public Task {
public:
  EthTask();
  virtual ~EthTask();

  virtual bool setup(System &system) override;
  virtual bool loop(System &system) override;

private:
};

#endif
