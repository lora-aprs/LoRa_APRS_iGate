#include "LoRa_APRS.h"

LoRa_APRS::LoRa_APRS() : _rxFrequency(433775000), _rxSpreadingFactor(12), _rxSignalBandwidth(125000), _rxCodingRate4(5), _txFrequency(433775000), _txSpreadingFactor(12), _txSignalBandwidth(125000), _txCodingRate4(5) {
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
  setSpreadingFactor(_txSpreadingFactor);
  setSignalBandwidth(_txSignalBandwidth);
  setCodingRate4(_txCodingRate4);
  setFrequency(_txFrequency);
  String data = msg->encode();
  beginPacket();
  // Header:
  write('<');
  write(0xFF);
  write(0x01);
  // APRS Data:
  write((const uint8_t *)data.c_str(), data.length());
  endPacket();
  setSpreadingFactor(_rxSpreadingFactor);
  setSignalBandwidth(_rxSignalBandwidth);
  setCodingRate4(_rxCodingRate4);
  setFrequency(_rxFrequency);
}

void LoRa_APRS::setRxFrequency(long frequency) {
  _rxFrequency = frequency;
  setFrequency(_rxFrequency);
}

// cppcheck-suppress unusedFunction
long LoRa_APRS::getRxFrequency() const {
  return _rxFrequency;
}

void LoRa_APRS::setTxFrequency(long frequency) {
  _txFrequency = frequency;
}

// cppcheck-suppress unusedFunction
long LoRa_APRS::getTxFrequency() const {
  return _txFrequency;
}

void LoRa_APRS::setRxSpreadingFactor(int spreadingFactor) {
  _rxSpreadingFactor = spreadingFactor;
  setSpreadingFactor(_rxSpreadingFactor);
}

// cppcheck-suppress unusedFunction
long LoRa_APRS::getRxSpreadingFactor() const {
  return _rxSpreadingFactor;
}

void LoRa_APRS::setRxSignalBandwidth(long signalBandwidth) {
  _rxSignalBandwidth = signalBandwidth;
  setSignalBandwidth(_rxSignalBandwidth);
}

// cppcheck-suppress unusedFunction
long LoRa_APRS::getRxSignalBandwidth() const {
  return _rxSignalBandwidth;
}

void LoRa_APRS::setRxCodingRate4(int codingRate) {
  _rxCodingRate4 = codingRate;
  setCodingRate4(_rxCodingRate4);
}

// cppcheck-suppress unusedFunction
long LoRa_APRS::getRxCodingRate4() const {
  return _rxCodingRate4;
}

void LoRa_APRS::setTxSpreadingFactor(int spreadingFactor) {
  _txSpreadingFactor = spreadingFactor;
}

// cppcheck-suppress unusedFunction
long LoRa_APRS::getTxSpreadingFactor() const {
  return _txSpreadingFactor;
}

void LoRa_APRS::setTxSignalBandwidth(long signalBandwidth) {
  _txSignalBandwidth = signalBandwidth;
}

// cppcheck-suppress unusedFunction
long LoRa_APRS::getTxSignalBandwidth() const {
  return _txSignalBandwidth;
}

void LoRa_APRS::setTxCodingRate4(int codingRate) {
  _txCodingRate4 = codingRate;
}

// cppcheck-suppress unusedFunction
long LoRa_APRS::getTxCodingRate4() const {
  return _txCodingRate4;
}
