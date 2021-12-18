#ifndef TASK_ROUTER_H_
#define TASK_ROUTER_H_

#include <APRSExtMessage.h>
#include <TaskManager.h>
#include <TelegramMessage.h>

class RouterTask : public Task {
public:
  RouterTask(TaskQueue<std::shared_ptr<APRSExtMessage>> &fromModem, TaskQueue<std::shared_ptr<APRSExtMessage>> &toModem, TaskQueue<std::shared_ptr<APRSExtMessage>> &toAprsIs, TaskQueue<std::shared_ptr<TelegramMessage>> &toTelegram);
  virtual ~RouterTask();

  virtual bool setup(System &system) override;
  virtual bool loop(System &system) override;

private:
  TaskQueue<std::shared_ptr<APRSExtMessage>> &_fromModem;
  TaskQueue<std::shared_ptr<APRSExtMessage>> &_toModem;
  TaskQueue<std::shared_ptr<APRSExtMessage>> &_toAprsIs;

  TaskQueue<std::shared_ptr<TelegramMessage>> &_toTelegram;

  std::shared_ptr<APRSExtMessage>  _beaconMsg;
  std::shared_ptr<TelegramMessage> _telegramMsg;
  Timer                            _beacon_timer;
};

#endif
