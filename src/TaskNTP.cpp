#include <logger.h>
#include <TimeLib.h>
#include "project_configuration.h"
#include "TaskNTP.h"
#include "Task.h"

NTPTask::NTPTask()
	: Task(TASK_NTP)
{
}

NTPTask::~NTPTask()
{
}

bool NTPTask::setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig)
{
	_ntpClient = std::shared_ptr<NTPClient>(new NTPClient(config->ntpServer.c_str()));
	_ntpClient->begin();
	while(!_ntpClient->forceUpdate())
	{
		logPrintlnW("NTP Client force update issue! Waiting 1 sek...");
		logPrintlnD(_ntpClient->getFormattedTime());
		//show_display("WARN", "NTP Client force update issue! Waiting 1 sek...", 1000);
		sleep(1);
	}
	setTime(_ntpClient->getEpochTime());
	logPrintI("Current time: ");
	logPrintlnI(_ntpClient->getFormattedTime());
	logPrintlnI("NTP Client init done!");
	//show_display("INFO", "NTP Client init done!", 2000);
	return true;
}

bool NTPTask::loop(std::shared_ptr<Configuration> config)
{
	if(_ntpClient->update())
	{
		setTime(_ntpClient->getEpochTime());
	}
	return true;
}
