#ifndef TASK_FTP_H_
#define TASK_FTP_H_

#include <TaskManager.h>
#include <ESP-FTP-Server-Lib.h>

class FTPTask : public Task
{
public:
	FTPTask();
	virtual ~FTPTask();

	virtual bool setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig) override;
	virtual bool loop(std::shared_ptr<Configuration> config) override;

private:
	std::shared_ptr<FTPServer> _ftpServer;
	bool _beginCalled;
};

#endif
