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
    logPrintlnE("Starting LoRa failed!");
    _stateInfo = "LoRa-Modem failed";
    _state     = Error;
    while (true)
      ;
  }
  _lora_aprs.setRxFrequency(system.getUserConfig()->lora.frequencyRx);
  _lora_aprs.setTxFrequency(system.getUserConfig()->lora.frequencyTx);
  _lora_aprs.setTxPower(system.getUserConfig()->lora.power);
  _lora_aprs.setRxSpreadingFactor(system.getUserConfig()->lora.spreadingFactorRx);
  _lora_aprs.setRxSignalBandwidth(system.getUserConfig()->lora.signalBandwidthRx);
  _lora_aprs.setRxCodingRate4(system.getUserConfig()->lora.codingRate4Rx);
  _lora_aprs.setTxSpreadingFactor(system.getUserConfig()->lora.spreadingFactorTx);
  _lora_aprs.setTxSignalBandwidth(system.getUserConfig()->lora.signalBandwidthTx);
  _lora_aprs.setTxCodingRate4(system.getUserConfig()->lora.codingRate4Tx);
  _lora_aprs.enableCrc();

  _stateInfo = "";
  return true;
}

bool ModemTask::loop(System &system) {
  if (_lora_aprs.checkMessage()) {
    std::shared_ptr<APRSMessage> msg = _lora_aprs.getMessage();
    // msg->getAPRSBody()->setData(msg->getAPRSBody()->getData() + " 123");
    logPrintD("[" + timeString() + "] ");
    logPrintD("Received packet '");
    logPrintD(msg->toString());
    logPrintD("' with RSSI ");
    logPrintD(String(_lora_aprs.packetRssi()));
    logPrintD(" and SNR ");
    logPrintlnD(String(_lora_aprs.packetSnr()));

    _fromModem.addElement(msg);
    system.getDisplay().addFrame(std::shared_ptr<DisplayFrame>(new TextFrame("LoRa", msg->toString())));
  }

  if (!_toModem.empty()) {
    std::shared_ptr<APRSMessage> msg = _toModem.getElement();
    _lora_aprs.sendMessage(msg);
  }

  return true;
}
