#ifndef LORA_H_
#define LORA_H_

#include <Arduino.h>

#include <APRS-Decoder.h>
#include <APRSExtMessage.h>
#include <LoRa.h>
#include <memory>

class LoRa_APRS : public LoRaClass {
public:
  LoRa_APRS();

  bool                            checkMessage();
  std::shared_ptr<APRSExtMessage> getMessage();

  void sendMessage(const std::shared_ptr<APRSExtMessage> msg);

  void setRxFrequency(long frequency);
  long getRxFrequency() const;

  void setTxFrequency(long frequency);
  long getTxFrequency() const;

private:
  std::shared_ptr<APRSExtMessage> _LastReceivedMsg;
  long                            _RxFrequency;
  long                            _TxFrequency;
};

#endif
