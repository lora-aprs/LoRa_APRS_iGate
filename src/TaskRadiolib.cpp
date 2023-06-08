#include <Task.h>
#include <TimeLib.h>
#include <logger.h>

#include "TaskRadiolib.h"

volatile bool RadiolibTask::_modemInterruptOccured = false;

RadiolibTask::RadiolibTask(TaskQueue<std::shared_ptr<APRSMessage>> &fromModem, TaskQueue<std::shared_ptr<APRSMessage>> &toModem) : Task(TASK_RADIOLIB, TaskRadiolib), _module(0), _radio(0), _rxEnable(false), _txEnable(false), _fromModem(fromModem), _toModem(toModem), _transmitFlag(false), _frequencyTx(0.0), _frequencyRx(0.0), _frequenciesAreSame(false) {
}

RadiolibTask::~RadiolibTask() {
  _radio->clearDio0Action();
}

bool RadiolibTask::setup(System &system) {
  SPI.begin(system.getBoardConfig()->Lora.Sck, system.getBoardConfig()->Lora.Miso, system.getBoardConfig()->Lora.Mosi, system.getBoardConfig()->Lora.CS);
  _module = new Module(system.getBoardConfig()->Lora.CS, system.getBoardConfig()->Lora.IRQ, system.getBoardConfig()->Lora.Reset);
  _radio  = new SX1278(_module);

  _rxEnable = true;
  _txEnable = system.getUserConfig()->lora.tx_enable;

  _frequencyTx = (float)system.getUserConfig()->lora.frequencyTx / 1000000;
  _frequencyRx = (float)system.getUserConfig()->lora.frequencyRx / 1000000;

  if (system.getUserConfig()->lora.frequencyTx == system.getUserConfig()->lora.frequencyRx) {
    _frequenciesAreSame = true;
  }

  float BWkHz = (float)system.getUserConfig()->lora.signalBandwidth / 1000;

  const uint16_t preambleLength = 8;

  int16_t state = _radio->begin(_frequencyRx, BWkHz, system.getUserConfig()->lora.spreadingFactor, system.getUserConfig()->lora.codingRate4, RADIOLIB_SX127X_SYNC_WORD, system.getUserConfig()->lora.power, preambleLength, system.getUserConfig()->lora.gainRx);
  if (state != RADIOLIB_ERR_NONE) {
    decodeError(system, state);
  }

  state = _radio->setCRC(true);
  if (state != RADIOLIB_ERR_NONE) {
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] setCRC failed, code %d", timeString().c_str(), state);
    decodeError(system, state);
  }

  _radio->setDio0Action(setFlag, RISING);

  if (_rxEnable) {
    startRX(system);
  }

  if (system.getUserConfig()->lora.tx_enable && system.getUserConfig()->lora.power > 17) {
    _radio->setCurrentLimit(140);
  }

  uint32_t preambleDurationMilliSec = ((uint64_t)(preambleLength + 4) << (system.getUserConfig()->lora.spreadingFactor + 10 /* to milli-sec */)) / system.getUserConfig()->lora.signalBandwidth;
  _txWaitTimer.setTimeout(preambleDurationMilliSec * 2);

  _stateInfo = "";
  return true;
}

bool RadiolibTask::loop(System &system) {
  if (_modemInterruptOccured) {
    handleModemInterrupt(system);
  } else if (_txWaitTimer.check() && !_toModem.empty()) {
    handleTXing(system);
  }
  return true;
}

void RadiolibTask::setFlag(void) {
  _modemInterruptOccured = true;
}

void RadiolibTask::handleModemInterrupt(System &system) {
  _modemInterruptOccured = false;

  if (_transmitFlag) { // transmitted
    _transmitFlag = false;
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_DEBUG, getName(), "[%s] TX done", timeString().c_str());
    _txWaitTimer.start();
    startRX(system);
    return;
  }

  // received
  String str;
  int    state = _radio->readData(str);
  if (state != RADIOLIB_ERR_NONE) {
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] readData failed, code %d", timeString().c_str(), state);
    return;
  }
  if (str.substring(0, 3) != "<\xff\x01") {
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_DEBUG, getName(), "[%s] Unknown packet '%s' with RSSI %.0fdBm, SNR %.2fdB and FreqErr %fHz", timeString().c_str(), str.c_str(), _radio->getRSSI(), _radio->getSNR(), -_radio->getFrequencyError());
    return;
  }

  std::shared_ptr<APRSMessage> msg = std::shared_ptr<APRSMessage>(new APRSMessage());
  msg->decode(str.substring(3));
  _fromModem.addElement(msg);
  system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_DEBUG, getName(), "[%s] Received packet '%s' with RSSI %.0fdBm, SNR %.2fdB and FreqErr %fHz", timeString().c_str(), msg->toString().c_str(), _radio->getRSSI(), _radio->getSNR(), -_radio->getFrequencyError());
  system.getDisplay().addFrame(std::shared_ptr<DisplayFrame>(new TextFrame("LoRa", msg->toString().c_str())));
}

void RadiolibTask::handleTXing(System &system) {
  if (!_txEnable) {
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_DEBUG, getName(), "[%s] TX is not enabled", timeString().c_str());
    _toModem.getElement(); // empty list, otherwise memory will get full.
    return;
  }

  static bool txsignaldetected_print = false;
  if (_transmitFlag) { // we are currently TXing, need to wait
    if (!txsignaldetected_print) {
      txsignaldetected_print = true;
      system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_DEBUG, getName(), "[%s] TX signal detected. Waiting TX", timeString().c_str());
    }
    return;
  }

  // we are currently RXing
  static bool rxsignaldetected_print = false;
  if (_frequenciesAreSame && (_radio->getModemStatus() & 0x01) == 0x01) {
    if (!rxsignaldetected_print) {
      rxsignaldetected_print = true;
      system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_DEBUG, getName(), "[%s] RX signal detected. Waiting TX", timeString().c_str());
    }
    return;
  }

  std::shared_ptr<APRSMessage> msg = _toModem.getElement();
  system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_DEBUG, getName(), "[%s] Transmitting packet '%s'", timeString().c_str(), msg->toString().c_str());
  startTX(system, "<\xff\x01" + msg->encode());
  rxsignaldetected_print = false;
  txsignaldetected_print = false;
}

void RadiolibTask::startRX(System &system) {
  if (!_frequenciesAreSame) {
    int16_t state = _radio->setFrequency(_frequencyRx);
    if (state != RADIOLIB_ERR_NONE) {
      system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] startRX failed, Freq update, code %d", timeString().c_str(), state);
      decodeError(system, state);
      return;
    }
  }

  int16_t state = _radio->startReceive();
  if (state != RADIOLIB_ERR_NONE) {
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] startRX failed, code %d", timeString().c_str(), state);
    decodeError(system, state);
  }
}

void RadiolibTask::startTX(System &system, String &str) {
  if (!_frequenciesAreSame) {
    int16_t state = _radio->setFrequency(_frequencyTx);
    if (state != RADIOLIB_ERR_NONE) {
      system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] startTX failed, Freq update, code %d", timeString().c_str(), state);
      decodeError(system, state);
      startRX(system);
      return;
    }
  }

  int16_t state = _radio->startTransmit(str);
  if (state != RADIOLIB_ERR_NONE) {
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] startTX failed, code %d", timeString().c_str(), state);
    decodeError(system, state);
    startRX(system);
    return;
  }
  _transmitFlag = true;
}

void RadiolibTask::decodeError(System &system, int16_t state) {
  switch (state) {
  case RADIOLIB_ERR_UNKNOWN:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 unknown error.", timeString().c_str());
    _rxEnable = false;
    _txEnable = false;
    break;
  case RADIOLIB_ERR_CHIP_NOT_FOUND:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 init failed, chip not found.", timeString().c_str());
    _rxEnable = false;
    _txEnable = false;
    break;
  case RADIOLIB_ERR_PACKET_TOO_LONG:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 packet too long.", timeString().c_str());
    break;
  case RADIOLIB_ERR_TX_TIMEOUT:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 tx timeout.", timeString().c_str());
    break;
  case RADIOLIB_ERR_RX_TIMEOUT:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 rx timeout.", timeString().c_str());
    break;
  case RADIOLIB_ERR_CRC_MISMATCH:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 crc mismatch.", timeString().c_str());
    break;
  case RADIOLIB_ERR_INVALID_BANDWIDTH:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 init failed, The supplied bandwidth value (%fkHz) is invalid for this module. Should be 7800, 10400, 15600, 20800, 31250, 41700 ,62500, 125000, 250000, 500000.", timeString().c_str(), system.getUserConfig()->lora.signalBandwidth / 1000);
    _rxEnable = false;
    _txEnable = false;
    break;
  case RADIOLIB_ERR_INVALID_SPREADING_FACTOR:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 init failed, The supplied spreading factor value (%d) is invalid for this module.", timeString().c_str(), system.getUserConfig()->lora.spreadingFactor);
    _rxEnable = false;
    _txEnable = false;
    break;
  case RADIOLIB_ERR_INVALID_CODING_RATE:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 init failed, The supplied coding rate value (%d) is invalid for this module.", timeString().c_str(), system.getUserConfig()->lora.codingRate4);
    _rxEnable = false;
    _txEnable = false;
    break;
  case RADIOLIB_ERR_INVALID_FREQUENCY:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 init failed, The supplied frequency value (%fMHz) is invalid for this module.", timeString().c_str(), _frequencyRx);
    _rxEnable = false;
    _txEnable = false;
    break;
  case RADIOLIB_ERR_INVALID_OUTPUT_POWER:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 init failed, The supplied output power value (%d) is invalid for this module.", timeString().c_str(), system.getUserConfig()->lora.power);
    _txEnable = false;
    break;
  case RADIOLIB_ERR_INVALID_CURRENT_LIMIT:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 init failed, The supplied current limit is invalid.", timeString().c_str());
    _txEnable = false;
    break;
  case RADIOLIB_ERR_INVALID_PREAMBLE_LENGTH:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 init failed, The supplied preamble length is invalid.", timeString().c_str());
    _txEnable = false;
    break;
  case RADIOLIB_ERR_INVALID_GAIN:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 init failed, The supplied gain value (%d) is invalid.", timeString().c_str(), system.getUserConfig()->lora.gainRx);
    _rxEnable = false;
    break;
  case RADIOLIB_ERR_WRONG_MODEM:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 init failed, wrong modem selected.", timeString().c_str());
    _rxEnable = false;
    _txEnable = false;
    break;
  case RADIOLIB_ERR_INVALID_NUM_SAMPLES:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 invalid number of samples.", timeString().c_str());
    break;
  case RADIOLIB_ERR_INVALID_RSSI_OFFSET:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 invalid RSSI offset.", timeString().c_str());
    break;
  case RADIOLIB_ERR_INVALID_ENCODING:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 invalid encoding.", timeString().c_str());
    break;
  case RADIOLIB_ERR_LORA_HEADER_DAMAGED:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 LoRa header damaged.", timeString().c_str());
    break;
  case RADIOLIB_ERR_INVALID_DIO_PIN:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 invalid DIO pin.", timeString().c_str());
    break;
  case RADIOLIB_ERR_INVALID_RSSI_THRESHOLD:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 invalid RSSI threshold.", timeString().c_str());
    break;
  case RADIOLIB_ERR_INVALID_BIT_RATE:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 invalid bit rate.", timeString().c_str());
    break;
  case RADIOLIB_ERR_INVALID_FREQUENCY_DEVIATION:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 invalid frequency deviation.", timeString().c_str());
    break;
  case RADIOLIB_ERR_INVALID_RX_BANDWIDTH:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 invalid rx bandwidth.", timeString().c_str());
    break;
  case RADIOLIB_ERR_INVALID_SYNC_WORD:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 invalid sync word.", timeString().c_str());
    break;
  case RADIOLIB_ERR_INVALID_DATA_SHAPING:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 invalid data shaping.", timeString().c_str());
    break;
  case RADIOLIB_ERR_INVALID_MODULATION:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 invalid modulation.", timeString().c_str());
    break;
  default:
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "[%s] SX1278 init failed, code %d", timeString().c_str(), state);
    _rxEnable = false;
    _txEnable = false;
  }
  _stateInfo = "LoRa-Modem failed";
  _state     = Error;
}
