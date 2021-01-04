#include <logger.h>
#include "TaskManager.h"

TaskManager::TaskManager()
{
}

void TaskManager::addTask(std::shared_ptr<Task> task)
{
	_tasks.push_back(task);
}

std::shared_ptr<Task> TaskManager::getTask(const char * name)
{
	for(std::shared_ptr<Task> & elem : _tasks)
	{
		if(elem->getName() == name)
		{
			return elem;
		}
	}
	return 0;
}

bool TaskManager::setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig)
{
	logPrintlnV("will setup all tasks...");
	for(std::shared_ptr<Task> & elem : _tasks)
	{
		logPrintW("call setup from ");
		logPrintlnW(elem->getName());
		if(!elem->setup(config, boardConfig))
		{
			return false;
		}
	}
	return true;
}

bool TaskManager::loop(std::shared_ptr<Configuration> config)
{
	//logPrintlnD("will loop all tasks...");
	for(std::shared_ptr<Task> & elem : _tasks)
	{
		//logPrintD("call loop from ");
		//logPrintlnD(elem->getName());
		if(!elem->loop(config))
		{
			return false;
		}
	}
	return true;
}