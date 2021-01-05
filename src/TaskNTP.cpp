#include <logger.h>
#include <TimeLib.h>
#include "project_configuration.h"
#include "TaskNTP.h"
#include "Task.h"

NTPTask::NTPTask()
	: Task(TASK_NTP), _beginCalled(false)
{
}

NTPTask::~NTPTask()
{
}

bool NTPTask::setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig)
{
	_ntpClient = std::shared_ptr<NTPClient>(new NTPClient(config->ntpServer.c_str()));
	return true;
}

bool NTPTask::loop(std::shared_ptr<Configuration> config)
{
	if(!_beginCalled)
	{
		_ntpClient->begin();
		_beginCalled = true;
	}
	if(_ntpClient->update())
	{
		setTime(_ntpClient->getEpochTime());
		logPrintI("Current time: ");
		logPrintlnI(_ntpClient->getFormattedTime());
	}
	return true;
}
