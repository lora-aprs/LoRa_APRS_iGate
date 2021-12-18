#ifndef LORA_H_
#define LORA_H_

#include <Arduino.h>

#include <APRS-Decoder.h>
#include <LoRa.h>
#include <memory>

class LoRa_APRS : public LoRaClass {
public:
  LoRa_APRS();

  bool                         checkMessage();
  std::shared_ptr<APRSMessage> getMessage();

  void sendMessage(const std::shared_ptr<APRSMessage> msg);

  void setRxFrequency(long frequency);
  long getRxFrequency() const;

  void setRxGain(uint8_t gain);

  void setTxFrequency(long frequency);
  long getTxFrequency() const;

private:
  std::shared_ptr<APRSMessage> _LastReceivedMsg;
  long                         _RxFrequency;
  long                         _TxFrequency;
};

#endif
