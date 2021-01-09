#include <logger.h>
#include "project_configuration.h"
#include "TaskOTA.h"
#include "Task.h"

OTATask::OTATask()
	: Task(TASK_OTA, TaskOta), _beginCalled(false)
{
}

OTATask::~OTATask()
{
}

bool OTATask::setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig)
{
	_ota = std::shared_ptr<ArduinoOTAClass>(new ArduinoOTAClass());
	_ota->onStart([&]()
		{
			String type;
			if (_ota->getCommand() == U_FLASH)
				type = "sketch";
			else // U_SPIFFS
				type = "filesystem";
			logPrintlnI("Start updating " + type);
		})
		.onEnd([]()
		{
			logPrintlnI("");
			logPrintlnI("OTA End");
		})
		.onProgress([](unsigned int progress, unsigned int total)
		{
			logPrintI("Progress: ");
			logPrintI(String(progress / (total / 100)));
			logPrintlnI("%");
		})
		.onError([](ota_error_t error)
		{
			logPrintE("Error[");
			logPrintE(String(error));
			logPrintE("]: ");
			if (error == OTA_AUTH_ERROR) logPrintlnE("Auth Failed");
			else if (error == OTA_BEGIN_ERROR) logPrintlnE("Begin Failed");
			else if (error == OTA_CONNECT_ERROR) logPrintlnE("Connect Failed");
			else if (error == OTA_RECEIVE_ERROR) logPrintlnE("Receive Failed");
			else if (error == OTA_END_ERROR) logPrintlnE("End Failed");
		});
	_ota->setHostname(config->callsign.c_str());
	return true;
}

bool OTATask::loop(std::shared_ptr<Configuration> config)
{
	if(!_beginCalled)
	{
		_ota->begin();
		_beginCalled = true;
	}
	_ota->handle();
	return true;
}
