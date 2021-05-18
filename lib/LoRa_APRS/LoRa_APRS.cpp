#include "LoRa_APRS.h"

LoRa_APRS::LoRa_APRS(BoardConfig const *const boardConfig) : _LastReceivedMsg(0), _RxFrequency(LORA_RX_FREQUENCY), _TxFrequency(LORA_TX_FREQUENCY) {
  SPI.begin(boardConfig->LoraSck, boardConfig->LoraMiso, boardConfig->LoraMosi, boardConfig->LoraCS);
  setPins(boardConfig->LoraCS, boardConfig->LoraReset, boardConfig->LoraIRQ);
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

// cppcheck-suppress unusedFunction
void LoRa_APRS::sendMessage(const std::shared_ptr<APRSMessage> msg) {
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
