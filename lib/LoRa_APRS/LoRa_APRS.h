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

  void setTxFrequency(long frequency);
  long getTxFrequency() const;

  void setRxSpreadingFactor(int spreadingFactor);
  long getRxSpreadingFactor() const;

  void setRxSignalBandwidth(long signalBandwidth);
  long getRxSignalBandwidth() const;

  void setRxCodingRate4(int codingRate);
  long getRxCodingRate4() const;

  void setTxSpreadingFactor(int spreadingFactor);
  long getTxSpreadingFactor() const;

  void setTxSignalBandwidth(long signalBandwidth);
  long getTxSignalBandwidth() const;

  void setTxCodingRate4(int codingRate);
  long getTxCodingRate4() const;

private:
  std::shared_ptr<APRSMessage> _LastReceivedMsg;
  long                         _rxFrequency;
  int                          _rxSpreadingFactor;
  long                         _rxSignalBandwidth;
  int                          _rxCodingRate4;
  long                         _txFrequency;
  int                          _txSpreadingFactor;
  long                         _txSignalBandwidth;
  int                          _txCodingRate4;
};

#endif
