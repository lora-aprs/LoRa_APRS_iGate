#include <logger.h>
#include <TimeLib.h>
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
	std::shared_ptr<StatusFrame> statusFrame = std::shared_ptr<StatusFrame>(new StatusFrame(TaskManager::instance().getTasks()));
	Display::instance().setStatusFrame(statusFrame);
	_stateInfo = "";
	return true;
}

bool DisplayTask::loop(std::shared_ptr<Configuration> config)
{
	Display::instance().update();
	return true;
}
