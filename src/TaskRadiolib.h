#ifndef TASK_LORA_H_
#define TASK_LORA_H_

#include "LoRaModem.h"
#include "System/TaskManager.h"
#include "project_configuration.h"
#include <APRS-Decoder.h>

class RadiolibTask : public Task {
public:
  explicit RadiolibTask(TaskQueue<std::shared_ptr<APRSMessage>> &fromModem, TaskQueue<std::shared_ptr<APRSMessage>> &_toModem);
  virtual ~RadiolibTask();

  virtual bool setup(System &system) override;
  virtual bool loop(System &system) override;

private:
  LoRaModem *_modem;

  bool _rxEnable;
  bool _txEnable;

  TaskQueue<std::shared_ptr<APRSMessage>> &_fromModem;
  TaskQueue<std::shared_ptr<APRSMessage>> &_toModem;

  static volatile bool _modemInterruptOccurred;

  Timer _txWaitTimer;

  bool _transmitFlag;

  float _frequencyTx;
  float _frequencyRx;
  bool  _frequenciesAreSame;

  static void setFlag(void);

  void startRX(System &system);
  void startTX(System &system, String &str);

  void handleModemInterrupt(System &system);
  void handleTXing(System &system);

  void decodeError(System &system, int16_t state);
};

#endif
