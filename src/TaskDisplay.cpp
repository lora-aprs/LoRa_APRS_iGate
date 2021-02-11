#include <logger.h>
#include <TimeLib.h>
#include "project_configuration.h"
#include "TaskDisplay.h"

DisplayTask::DisplayTask()
	: Task("DisplayTask", 0)
{
}

DisplayTask::~DisplayTask()
{
}

bool DisplayTask::setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig)
{
	Display::instance().setup(boardConfig);
	if(config->display.turn180)
	{
		Display::instance().turn180();
	}
	std::shared_ptr<StatusFrame> statusFrame = std::shared_ptr<StatusFrame>(new StatusFrame(TaskManager::instance().getTasks()));
	Display::instance().setStatusFrame(statusFrame);
	_stateInfo = config->callsign;
	return true;
}

bool DisplayTask::loop(std::shared_ptr<Configuration> config)
{
	Display::instance().update();
	return true;
}
