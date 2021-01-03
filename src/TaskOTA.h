#ifndef TASK_OTA_H_
#define TASK_OTA_H_

#include <TaskManager.h>
#include <ArduinoOTA.h>

class OTATask : public Task
{
public:
	OTATask();
	virtual ~OTATask();

	virtual bool setup(std::shared_ptr<Configuration> config) override;
	virtual bool loop(std::shared_ptr<Configuration> config) override;

private:
	std::shared_ptr<ArduinoOTAClass> _ota;
};

#endif
