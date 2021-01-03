#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_

#include <list>
#include <memory>
#include <Arduino.h>
#include <configuration.h>

class Task
{
public:
	Task(String & name) : _name(name) {}
	Task(const char * name) : _name(name) {}
	virtual ~Task() {}

	String getName() const { return _name; }

	virtual bool setup(std::shared_ptr<Configuration> config) = 0;
	virtual bool loop(std::shared_ptr<Configuration> config) = 0;

private:
	String _name;
};

class TaskManager
{
public:
	TaskManager();

	void addTask(std::shared_ptr<Task> task);
	std::shared_ptr<Task> getTask(String & name);

	bool setup(std::shared_ptr<Configuration> config);
	bool loop(std::shared_ptr<Configuration> config);

private:
	std::list<std::shared_ptr<Task>> _tasks;

};

#endif
