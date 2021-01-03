#include <logger.h>
#include "project_configuration.h"
#include "TaskLora.h"

LoraTask::LoraTask()
	: Task("LoraTask")
{
}

LoraTask::~LoraTask()
{
}

bool LoraTask::setup(std::shared_ptr<Configuration> config)
{
	return true;
}

bool LoraTask::setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig)
{
	_lora_aprs = std::shared_ptr<LoRa_APRS>(new LoRa_APRS(boardConfig));
	if(!_lora_aprs->begin(_lora_aprs->getRxFrequency()))
	{
		logPrintlnE("Starting LoRa failed!");
		//show_display("ERROR", "Starting LoRa failed!");
		while(true);
	}
	_lora_aprs->setRxFrequency(config->lora.frequencyRx);
	_lora_aprs->setTxFrequency(config->lora.frequencyTx);
	_lora_aprs->setTxPower(config->lora.power);
	_lora_aprs->setSpreadingFactor(config->lora.spreadingFactor);
	_lora_aprs->setSignalBandwidth(config->lora.signalBandwidth);
	_lora_aprs->setCodingRate4(config->lora.codingRate4);
	_lora_aprs->enableCrc();
	logPrintlnI("LoRa init done!");
	//show_display("INFO", "LoRa init done!", 2000);

	return true;
}

bool LoraTask::loop(std::shared_ptr<Configuration> config)
{
	_lora_aprs->checkMessage();
	return true;
}
