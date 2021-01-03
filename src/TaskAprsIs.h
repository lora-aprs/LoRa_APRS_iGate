#ifndef TASK_APRS_IS_H_
#define TASK_APRS_IS_H_

#include <TaskManager.h>
#include <APRS-IS.h>
#include <APRSMessage.h>

class AprsIsTask : public Task
{
public:
	AprsIsTask();
	virtual ~AprsIsTask();

	virtual bool setup(std::shared_ptr<Configuration> config) override;
	virtual bool loop(std::shared_ptr<Configuration> config) override;

private:
	std::shared_ptr<APRS_IS> _aprs_is;
	std::shared_ptr<APRSMessage> _beaconMsg;
	time_t _beacon_next_time;

	void connect(std::shared_ptr<Configuration> config);
};

#endif
