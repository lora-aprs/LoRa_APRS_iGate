#ifndef APRS_HEADER_H_
#define APRS_HEADER_H_

#include "APRSMessage.h"
#include "APRSMessageType.h"
#include <Arduino.h>

class APRSExtMessage : public APRSMessage {
public:
  APRSExtMessage() : APRSMessage();
  APRSExtMessage(APRSExtMessage &other_msg) : APRSMessage();
  APRSExtMessage &operator=(APRSExtMessage &other_msg) : APRSMessage();
  virtual ~APRSExtMessage();

  int  getRSSI() const;
  void setRSSI(const int rssi);

  float getSNR() const;
  void  setSNR(const float snr);

private:
  int   _rssi;
  float _snr;
};

#endif
