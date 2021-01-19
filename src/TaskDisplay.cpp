#include <logger.h>
#include <TimeLib.h>
#include "project_configuration.h"
#include "TaskDisplay.h"
#include "Task.h"

DisplayTask::DisplayTask()
	: Task(TASK_DISPLAY, TaskDisplay), _beginCalled(false)
{
}

DisplayTask::~DisplayTask()
{
}

bool DisplayTask::setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig)
{
	Display::instance().setup(boardConfig);
	return true;
}

bool DisplayTask::loop(std::shared_ptr<Configuration> config)
{
	if(!_beginCalled)
	{
		_beginCalled = true;
	}
	Display::instance().update();
	return true;
}
