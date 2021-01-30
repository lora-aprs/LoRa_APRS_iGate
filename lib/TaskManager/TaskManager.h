#ifndef TASK_MANAGER_H_
#define TASK_MANAGER_H_

#include <list>
#include <memory>
#include <Arduino.h>
#include <configuration.h>
#include <BoardFinder.h>
#include <Display.h>

#include "TaskQueue.h"

enum TaskDisplayState
{
	Error,
	Warning,
	Okay,
};

class Task
{
public:
	Task(String & name, int taskId) : _state(Okay), _stateInfo("Booting"), _name(name), _taskId(taskId) {}
	Task(const char * name, int taskId) : _state(Okay), _stateInfo("Booting"), _name(name), _taskId(taskId) {}
	virtual ~Task() {}

	String getName() const { return _name; }
	int getTaskId() const { return _taskId; }

	TaskDisplayState getState() const { return _state; }
	String getStateInfo() const { return _stateInfo; }

	virtual bool setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig) = 0;
	virtual bool loop(std::shared_ptr<Configuration> config) = 0;

protected:
	TaskDisplayState _state;
	String _stateInfo;

private:
	String _name;
	int _taskId;
};

class TaskManager
{
public:
	static TaskManager & instance()
	{
		static TaskManager _instance;
		return _instance;
	}

	~TaskManager() {}

	void addTask(std::shared_ptr<Task> task);
	std::shared_ptr<Task> getTask(const char * name);
	std::list<std::shared_ptr<Task>> getTasks();

	bool setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig);
	bool loop(std::shared_ptr<Configuration> config);

private:
	std::list<std::shared_ptr<Task>> _tasks;

	TaskManager();
	TaskManager(const TaskManager &);
	TaskManager & operator = (const TaskManager &);
};

class StatusFrame : public DisplayFrame
{
public:
	explicit StatusFrame(const std::list<std::shared_ptr<Task>> & tasks) : _tasks(tasks) {}
	virtual ~StatusFrame() {}
	void drawStatusPage(Bitmap & bitmap) override;

	bool isPrio() const;

private:
	std::list<std::shared_ptr<Task>> _tasks;
};

#endif
