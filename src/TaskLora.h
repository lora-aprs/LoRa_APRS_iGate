#ifndef TASK_LORA_H_
#define TASK_LORA_H_

#include <BoardFinder.h>
#include <LoRa_APRS.h>
#include <TaskManager.h>

class LoraTask : public Task {
public:
  LoraTask();
  virtual ~LoraTask();

  virtual bool setup(std::shared_ptr<System> system) override;
  virtual bool loop(std::shared_ptr<System> system) override;

  TaskQueue<std::shared_ptr<APRSMessage>> inputQueue;

private:
  std::shared_ptr<LoRa_APRS> _lora_aprs;
};

#endif
