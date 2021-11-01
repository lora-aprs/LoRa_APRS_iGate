#ifndef APRS_EXTHEADER_H_
#define APRS_EXTHEADER_H_

#include <APRSMessage.h>
#include <APRSMessageType.h>
#include <Arduino.h>

class APRSExtMessage : public APRSMessage {
public:
  APRSExtMessage();
  /*
  APRSExtMessage(APRSExtMessage &other_msg);
  APRSExtMessage &operator=(APRSExtMessage &other_msg);
  */
  virtual ~APRSExtMessage();

  int  getRSSI() const;
  void setRSSI(const int rssi);

  float getSNR() const;
  void  setSNR(const float snr);

  virtual String toString();

private:
  int   _rssi = 0;
  float _snr  = 0.0;
};

#endif
