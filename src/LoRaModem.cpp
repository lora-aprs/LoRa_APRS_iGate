#include "LoRaModem.h"

// SX1278
#ifdef USE_SX1278
Modem_SX1278::Modem_SX1278() : _radio(0) {
}

int16_t Modem_SX1278::begin(const Configuration::LoRa &lora_config, const uint16_t preambleLength, void (*setFlag)()) {
  float _frequencyRx = (float)lora_config.frequencyRx / 1000000;
  float BWkHz        = (float)lora_config.signalBandwidth / 1000;

#if defined(LORA_SCK) && defined(LORA_MISO) && defined(LORA_MOSI) && defined(LORA_CS)
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  _module = new Module(LORA_CS, LORA_IRQ, LORA_RST);
#else
  SPI.begin(SCK, MISO, MOSI, SS);
  _module = new Module(SS, DIO0, RST_LoRa);
#endif

  _radio        = new SX1278(_module);
  int16_t state = _radio->begin(_frequencyRx, BWkHz, lora_config.spreadingFactor, lora_config.codingRate4, RADIOLIB_SX127X_SYNC_WORD, lora_config.power, preambleLength, lora_config.gainRx);
  if (state != RADIOLIB_ERR_NONE) {
    return state;
  }

  state = _radio->setCRC(true);
  if (state != RADIOLIB_ERR_NONE) {
    return state;
  }

  _radio->setDio0Action(setFlag, RISING);

  if (lora_config.tx_enable && lora_config.power > 17) {
    _radio->setCurrentLimit(140);
  }
  return RADIOLIB_ERR_NONE;
}

int16_t Modem_SX1278::readData(String &str) {
  return _radio->readData(str);
}

int16_t Modem_SX1278::setFrequency(float freq) {
  return _radio->setFrequency(freq);
}

int16_t Modem_SX1278::startReceive() {
  return _radio->startReceive();
}

int16_t Modem_SX1278::startTransmit(String &str) {
  return _radio->startTransmit(str);
}

int16_t Modem_SX1278::receive(String &str) {
  return _radio->receive(str);
}

float Modem_SX1278::getRSSI() {
  return _radio->getRSSI();
}

float Modem_SX1278::getSNR() {
  return _radio->getSNR();
}

float Modem_SX1278::getFrequencyError() {
  return _radio->getFrequencyError();
}

uint8_t Modem_SX1278::getModemStatus() {
  return _radio->getModemStatus();
}

// SX1262
#elif defined(USE_SX1268)
Modem_SX1268::Modem_SX1268() : _radio(0) {
}

int16_t Modem_SX1268::begin(const Configuration::LoRa &lora_config, const uint16_t preambleLength, void (*setFlag)()) {
  float _frequencyRx = (float)lora_config.frequencyRx / 1000000;
  float BWkHz        = (float)lora_config.signalBandwidth / 1000;

#if defined(LORA_SCK) && defined(LORA_MISO) && defined(LORA_MOSI) && defined(LORA_CS)
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  _module = new Module(LORA_CS, LORA_IRQ, LORA_RST, BUSY_LoRa);
#else
  SPI.begin(SCK, MISO, MOSI, SS);
  _module = new Module(SS, DIO0, RST_LoRa, BUSY_LoRa);
#endif

  _radio        = new SX1262(_module);
  int16_t state = _radio->begin(_frequencyRx, BWkHz, lora_config.spreadingFactor, lora_config.codingRate4, RADIOLIB_SX126X_SYNC_WORD_PRIVATE, lora_config.power, preambleLength);
  if (state != RADIOLIB_ERR_NONE) {
    return state;
  }

  state = _radio->setCRC(true);
  if (state != RADIOLIB_ERR_NONE) {
    return state;
  }

  _radio->setDio1Action(setFlag);

  if (lora_config.tx_enable && lora_config.power > 17) {
    _radio->setCurrentLimit(140);
  }
  return RADIOLIB_ERR_NONE;
}

int16_t Modem_SX1268::readData(String &str) {
  return _radio->readData(str);
}

int16_t Modem_SX1268::setFrequency(float freq) {
  return _radio->setFrequency(freq);
}

int16_t Modem_SX1268::startReceive() {
  return _radio->startReceive();
}

int16_t Modem_SX1268::startTransmit(String &str) {
  return _radio->startTransmit(str);
}

int16_t Modem_SX1268::receive(String &str) {
  return _radio->receive(str);
}

float Modem_SX1268::getRSSI() {
  return _radio->getRSSI();
}

float Modem_SX1268::getSNR() {
  return _radio->getSNR();
}

float Modem_SX1268::getFrequencyError() {
  return _radio->getFrequencyError();
}

uint8_t Modem_SX1268::getModemStatus() {
  return 0;
}
#endif
