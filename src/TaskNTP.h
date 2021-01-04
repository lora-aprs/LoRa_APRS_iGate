#ifndef TASK_NTP_H_
#define TASK_NTP_H_

#include <TaskManager.h>
#include <NTPClient.h>

class NTPTask : public Task
{
public:
	NTPTask();
	virtual ~NTPTask();

	virtual bool setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig) override;
	virtual bool loop(std::shared_ptr<Configuration> config) override;

private:
	std::shared_ptr<NTPClient> _ntpClient;
};

#endif
