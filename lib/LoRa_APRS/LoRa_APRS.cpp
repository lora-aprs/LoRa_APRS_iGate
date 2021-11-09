#include "LoRa_APRS.h"

LoRa_APRS::LoRa_APRS() : _RxFrequency(433775000), _TxFrequency(433775000) {
}

bool LoRa_APRS::checkMessage() {
  if (!parsePacket()) {
    return false;
  }
  // read header:
  char dummy[4];
  readBytes(dummy, 3);
  if (dummy[0] != '<') {
    // is no APRS message, ignore message
    while (available()) {
      read();
    }
    return false;
  }
  // read APRS data:
  String str;
  while (available()) {
    str += (char)read();
  }
  _LastReceivedMsg = std::shared_ptr<APRSExtMessage>(new APRSExtMessage());
  _LastReceivedMsg->decode(str);
  return true;
}

std::shared_ptr<APRSExtMessage> LoRa_APRS::getMessage() {
  return _LastReceivedMsg;
}

void LoRa_APRS::sendMessage(const std::shared_ptr<APRSExtMessage> msg) {
  setFrequency(_TxFrequency);
  String data = msg->encode();
  beginPacket();
  // Header:
  write('<');
  write(0xFF);
  write(0x01);
  // APRS Data:
  write((const uint8_t *)data.c_str(), data.length());
  endPacket();
  setFrequency(_RxFrequency);
}

void LoRa_APRS::setRxFrequency(long frequency) {
  _RxFrequency = frequency;
  setFrequency(_RxFrequency);
}

void LoRa_APRS::setRxGain(uint8_t gain) {
  setGain(gain);
}

// cppcheck-suppress unusedFunction
long LoRa_APRS::getRxFrequency() const {
  return _RxFrequency;
}

void LoRa_APRS::setTxFrequency(long frequency) {
  _TxFrequency = frequency;
}

// cppcheck-suppress unusedFunction
long LoRa_APRS::getTxFrequency() const {
  return _TxFrequency;
}
