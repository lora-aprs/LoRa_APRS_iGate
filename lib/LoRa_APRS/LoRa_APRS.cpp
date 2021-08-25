#include "LoRa_APRS.h"

LoRa_APRS::LoRa_APRS() : _RxFrequency(433775000), _TxFrequency(433775000), _RxSpreadingFactor(12), _RxSignalBandwidth(125000), _RxCodingRate4(5), _TxSpreadingFactor(12), _TxSignalBandwidth(125000), _TxCodingRate4(5) {
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
  _LastReceivedMsg = std::shared_ptr<APRSMessage>(new APRSMessage());
  _LastReceivedMsg->decode(str);
  return true;
}

std::shared_ptr<APRSMessage> LoRa_APRS::getMessage() {
  return _LastReceivedMsg;
}

void LoRa_APRS::sendMessage(const std::shared_ptr<APRSMessage> msg) {
  setSpreadingFactor(_TxSpreadingFactor);
  setSignalBandwidth(_TxSignalBandwidth);
  setCodingRate4(_TxCodingRate4);
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
  setSpreadingFactor(_RxSpreadingFactor);
  setSignalBandwidth(_RxSignalBandwidth);
  setCodingRate4(_RxCodingRate4);
  setFrequency(_RxFrequency);
}

void LoRa_APRS::setRxFrequency(long frequency) {
  _RxFrequency = frequency;
  setFrequency(_RxFrequency);
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

void LoRa_APRS::setRxSpreadingFactor(int spreadingFactor) {
  _RxSpreadingFactor = spreadingFactor;
  setSpreadingFactor(_RxSpreadingFactor);
}

// cppcheck-suppress unusedFunction
long LoRa_APRS::getRxSpreadingFactor() const {
  return _RxSpreadingFactor;
}

void LoRa_APRS::setRxSignalBandwidth(long signalBandwidth) {
  _RxSignalBandwidth = signalBandwidth;
  setSignalBandwidth(_RxSignalBandwidth);
}

// cppcheck-suppress unusedFunction
long LoRa_APRS::getRxSignalBandwidth() const {
  return _RxSignalBandwidth;
}

void LoRa_APRS::setRxCodingRate4(int codingRate) {
  _RxCodingRate4 = codingRate;
  setCodingRate4(_RxCodingRate4);
}

// cppcheck-suppress unusedFunction
long LoRa_APRS::getRxCodingRate4() const {
  return _RxCodingRate4;
}

void LoRa_APRS::setTxSpreadingFactor(int spreadingFactor) {
  _TxSpreadingFactor = spreadingFactor;
}

// cppcheck-suppress unusedFunction
long LoRa_APRS::getTxSpreadingFactor() const {
  return _TxSpreadingFactor;
}

void LoRa_APRS::setTxSignalBandwidth(long signalBandwidth) {
  _TxSignalBandwidth = signalBandwidth;
}

// cppcheck-suppress unusedFunction
long LoRa_APRS::getTxSignalBandwidth() const {
  return _TxSignalBandwidth;
}

void LoRa_APRS::setTxCodingRate4(int codingRate) {
  _TxCodingRate4 = codingRate;
}

// cppcheck-suppress unusedFunction
long LoRa_APRS::getTxCodingRate4() const {
  return _TxCodingRate4;
}
