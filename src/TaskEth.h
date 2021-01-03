#ifndef TASK_ETH_H_
#define TASK_ETH_H_

#include <TaskManager.h>

class EthTask : public Task
{
public:
	EthTask();
	virtual ~EthTask();

	virtual bool setup(std::shared_ptr<Configuration> config) override;
	virtual bool loop(std::shared_ptr<Configuration> config) override;

private:
};

#endif
