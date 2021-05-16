#ifndef TASK_LORA_H_
#define TASK_LORA_H_

#include <BoardFinder.h>
#include <LoRa_APRS.h>
#include <TaskManager.h>

class ModemTask : public Task {
public:
  ModemTask(TaskQueue<std::shared_ptr<APRSMessage>> & fromModem);
  virtual ~ModemTask();

  virtual bool setup(std::shared_ptr<System> system) override;
  virtual bool loop(std::shared_ptr<System> system) override;

private:
  std::shared_ptr<LoRa_APRS>                     _lora_aprs;
  TaskQueue<std::shared_ptr<APRSMessage>> & _fromModem;
};

#endif
