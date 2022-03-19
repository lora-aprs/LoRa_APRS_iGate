#include <logger.h>

#include <TimeLib.h>

#include "Task.h"
#include "TaskAprsIs.h"
#include "TaskModem.h"
#include "project_configuration.h"

ModemTask::ModemTask(TaskQueue<std::shared_ptr<APRSMessage>> &fromModem, TaskQueue<std::shared_ptr<APRSMessage>> &toModem) : Task(TASK_MODEM, TaskModem), _lora_aprs(), _fromModem(fromModem), _toModem(toModem) {
}

ModemTask::~ModemTask() {
}

bool ModemTask::setup(System &system) {
  SPI.begin(system.getBoardConfig()->LoraSck, system.getBoardConfig()->LoraMiso, system.getBoardConfig()->LoraMosi, system.getBoardConfig()->LoraCS);
  _lora_aprs.setPins(system.getBoardConfig()->LoraCS, system.getBoardConfig()->LoraReset, system.getBoardConfig()->LoraIRQ);
  if (!_lora_aprs.begin(system.getUserConfig()->lora.frequencyRx)) {
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, getName(), "Starting LoRa failed!");
    _stateInfo = "LoRa-Modem failed";
    _state     = Error;
    while (true)
      ;
  }
  _lora_aprs.setRxFrequency(system.getUserConfig()->lora.frequencyRx);
  _lora_aprs.setRxGain(system.getUserConfig()->lora.gainRx);
  _lora_aprs.setTxFrequency(system.getUserConfig()->lora.frequencyTx);
  _lora_aprs.setTxPower(system.getUserConfig()->lora.power);
  _lora_aprs.setSpreadingFactor(system.getUserConfig()->lora.spreadingFactor);
  _lora_aprs.setSignalBandwidth(system.getUserConfig()->lora.signalBandwidth);
  _lora_aprs.setCodingRate4(system.getUserConfig()->lora.codingRate4);
  _lora_aprs.enableCrc();

  _stateInfo = "";
  return true;
}

bool ModemTask::loop(System &system) {
  if (_lora_aprs.checkMessage()) {
    std::shared_ptr<APRSMessage> msg = _lora_aprs.getMessage();
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_DEBUG, getName(), "[%s] Received packet '%s' with RSSI %d and SNR %f", timeString(), msg->toString(), _lora_aprs.packetRssi(), _lora_aprs.packetSnr());
    _fromModem.addElement(msg);
    system.getDisplay().addFrame(std::shared_ptr<DisplayFrame>(new TextFrame("LoRa", msg->toString())));
  }

  if (!_toModem.empty()) {
    std::shared_ptr<APRSMessage> msg = _toModem.getElement();
    if (system.getUserConfig()->lora.tx_enable) {
      system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_DEBUG, getName(), "[%s] Transmitting packet '%s'", timeString(), msg->toString());
      _lora_aprs.sendMessage(msg);
      system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_DEBUG, getName(), "[%s] TX done", timeString());
    } else {
      system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_DEBUG, getName(), "[%s] NOT transmitting packet as TX is not enabled '%s'", timeString(), msg->toString());
    }
  }

  return true;
}
