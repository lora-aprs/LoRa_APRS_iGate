#ifndef TASK_DISPLAY_H_
#define TASK_DISPLAY_H_

#include <Display.h>
#include <TaskManager.h>

class DisplayTask : public Task
{
public:
	DisplayTask();
	virtual ~DisplayTask();

	virtual bool setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig) override;
	virtual bool loop(std::shared_ptr<Configuration> config) override;
};

#endif
