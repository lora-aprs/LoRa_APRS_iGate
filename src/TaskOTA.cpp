#include <logger.h>
#include "project_configuration.h"
#include "TaskOTA.h"

OTATask::OTATask()
	: Task("OTATask")
{
}

OTATask::~OTATask()
{
}

bool OTATask::setup(std::shared_ptr<Configuration> config)
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
			//show_display("OTA UPDATE", "Start update", type);
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
			//show_display("OTA UPDATE", "Progress: ", String(progress / (total / 100)) + "%");
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
	_ota->begin();
	logPrintlnI("OTA init done!");
	return true;
}

bool OTATask::loop(std::shared_ptr<Configuration> config)
{
	_ota->handle();
	return true;
}
