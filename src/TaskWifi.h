#ifndef TASK_WIFI_H_
#define TASK_WIFI_H_

#include <TaskManager.h>
#include <WiFiMulti.h>

class WifiTask : public Task
{
public:
	WifiTask();
	virtual ~WifiTask();

	virtual bool setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig) override;
	virtual bool loop(std::shared_ptr<Configuration> config) override;

private:
	std::shared_ptr<WiFiMulti> _wiFiMulti;
	uint8_t _oldWifiStatus;
};

#endif
