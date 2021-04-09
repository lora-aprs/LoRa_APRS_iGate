#include <TimeLib.h>
#include <logger.h>

#include "Task.h"
#include "TaskAprsIs.h"
#include "TaskLora.h"
#include "project_configuration.h"

LoraTask::LoraTask() : Task(TASK_LORA, TaskLora) {
}

LoraTask::~LoraTask() {
}

bool LoraTask::setup(std::shared_ptr<System> system) {
  _lora_aprs = std::shared_ptr<LoRa_APRS>(new LoRa_APRS(system->getBoardConfig()));
  if (!_lora_aprs->begin(_lora_aprs->getRxFrequency())) {
    logPrintlnE("Starting LoRa failed!");
    _stateInfo = "LoRa-Modem failed";
    _state     = Error;
    while (true)
      ;
  }
  _lora_aprs->setRxFrequency(system->getUserConfig()->lora.frequencyRx);
  _lora_aprs->setTxFrequency(system->getUserConfig()->lora.frequencyTx);
  _lora_aprs->setTxPower(system->getUserConfig()->lora.power);
  _lora_aprs->setSpreadingFactor(system->getUserConfig()->lora.spreadingFactor);
  _lora_aprs->setSignalBandwidth(system->getUserConfig()->lora.signalBandwidth);
  _lora_aprs->setCodingRate4(system->getUserConfig()->lora.codingRate4);
  _lora_aprs->enableCrc();

  _stateInfo = "";
  return true;
}

bool LoraTask::loop(std::shared_ptr<System> system) {
  if (_lora_aprs->checkMessage()) {
    std::shared_ptr<APRSMessage> msg = _lora_aprs->getMessage();
    // msg->getAPRSBody()->setData(msg->getAPRSBody()->getData() + " 123");
    logPrintD("[" + timeString() + "] ");
    logPrintD("Received packet '");
    logPrintD(msg->toString());
    logPrintD("' with RSSI ");
    logPrintD(String(_lora_aprs->packetRssi()));
    logPrintD(" and SNR ");
    logPrintlnD(String(_lora_aprs->packetSnr()));

    String path = msg->getPath();
    if (path.indexOf("RFONLY") != -1 || path.indexOf("NOGATE") != -1 || path.indexOf("TCPIP") != -1) {
      return true;
    }

    if (!path.isEmpty()) {
      path += ",";
    }
    msg->setPath(path + "qAR," + system->getUserConfig()->callsign);

    std::shared_ptr<AprsIsTask> is_thread = std::static_pointer_cast<AprsIsTask>(system->getTaskManager().getTask(TASK_APRS_IS));
    is_thread->inputQueue.addElement(msg);
    system->getDisplay().addFrame(std::shared_ptr<DisplayFrame>(new TextFrame("LoRa", msg->toString())));
  }

  if (!inputQueue.empty()) {
    std::shared_ptr<APRSMessage> msg = inputQueue.getElement();
    _lora_aprs->sendMessage(msg);
  }

  return true;
}
