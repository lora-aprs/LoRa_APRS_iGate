#ifndef LORA_MODEM_H_
#define LORA_MODEM_H_

#include <RadioLib.h>

#include "project_configuration.h"

class LoRaModem {
public:
  LoRaModem() : _module(0) {
  }

  virtual ~LoRaModem() {
  }

  virtual int16_t begin(const Configuration::LoRa &lora_config, const uint16_t preambleLength, void (*setFlag)()) = 0;

  virtual int16_t readData(String &str) = 0;

  virtual int16_t setFrequency(float freq)   = 0;
  virtual int16_t startReceive()             = 0;
  virtual int16_t startTransmit(String &str) = 0;

  virtual int16_t receive(String &str) = 0;

  virtual float   getRSSI()           = 0;
  virtual float   getSNR()            = 0;
  virtual float   getFrequencyError() = 0;
  virtual uint8_t getModemStatus()    = 0;

protected:
  Module *_module;
};

#ifdef USE_SX1278
class Modem_SX1278 : public LoRaModem {
public:
  Modem_SX1278();

  int16_t begin(const Configuration::LoRa &lora_config, const uint16_t preambleLength, void (*setFlag)()) override;

  int16_t readData(String &str) override;

  int16_t setFrequency(float freq) override;
  int16_t startReceive() override;
  int16_t startTransmit(String &str) override;

  int16_t receive(String &str) override;

  float   getRSSI() override;
  float   getSNR() override;
  float   getFrequencyError() override;
  uint8_t getModemStatus() override;

private:
  SX1278 *_radio;
};

#elif defined(USE_SX1268)
class Modem_SX1268 : public LoRaModem {
public:
  Modem_SX1268();

  int16_t begin(const Configuration::LoRa &lora_config, const uint16_t preambleLength, void (*setFlag)()) override;

  int16_t readData(String &str) override;

  int16_t setFrequency(float freq) override;
  int16_t startReceive() override;
  int16_t startTransmit(String &str) override;

  int16_t receive(String &str) override;

  float   getRSSI() override;
  float   getSNR() override;
  float   getFrequencyError() override;
  uint8_t getModemStatus() override;

private:
  SX1262 *_radio;
};
#endif

#endif
