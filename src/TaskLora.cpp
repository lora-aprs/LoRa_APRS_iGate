#include <logger.h>
#include <TimeLib.h>
#include "project_configuration.h"
#include "TaskLora.h"
#include "TaskAprsIs.h"
#include "Task.h"

LoraTask::LoraTask()
	: Task(TASK_LORA, TaskLora)
{
}

LoraTask::~LoraTask()
{
}

bool LoraTask::setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig)
{
	_lora_aprs = std::shared_ptr<LoRa_APRS>(new LoRa_APRS(boardConfig));
	if(!_lora_aprs->begin(_lora_aprs->getRxFrequency()))
	{
		logPrintlnE("Starting LoRa failed!");
		while(true);
	}
	_lora_aprs->setRxFrequency(config->lora.frequencyRx);
	_lora_aprs->setTxFrequency(config->lora.frequencyTx);
	_lora_aprs->setTxPower(config->lora.power);
	_lora_aprs->setSpreadingFactor(config->lora.spreadingFactor);
	_lora_aprs->setSignalBandwidth(config->lora.signalBandwidth);
	_lora_aprs->setCodingRate4(config->lora.codingRate4);
	_lora_aprs->enableCrc();

	return true;
}

bool LoraTask::loop(std::shared_ptr<Configuration> config)
{
	if(_lora_aprs->checkMessage())
	{
		std::shared_ptr<APRSMessage> msg = _lora_aprs->getMessage();
		//msg->getAPRSBody()->setData(msg->getAPRSBody()->getData() + " 123");
		logPrintD("[" + timeString() + "] ");
		logPrintD("Received packet '");
		logPrintD(msg->toString());
		logPrintD("' with RSSI ");
		logPrintD(String(_lora_aprs->packetRssi()));
		logPrintD(" and SNR ");
		logPrintlnD(String(_lora_aprs->packetSnr()));
		std::shared_ptr<AprsIsTask> is_thread = std::static_pointer_cast<AprsIsTask>(TaskManager::instance().getTask(TASK_APRS_IS));
		is_thread->inputQueue.addElement(msg);
	}

	if(!inputQueue.empty())
	{
		std::shared_ptr<APRSMessage> msg = inputQueue.getElement();
		_lora_aprs->sendMessage(msg);
	}

	return true;
}
