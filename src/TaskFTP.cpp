#include <SPIFFS.h>
#include <FTPFilesystem.h>
#include <logger.h>
#include "project_configuration.h"
#include "TaskFTP.h"
#include "Task.h"

FTPTask::FTPTask()
	: Task(TASK_FTP, TaskFtp), _beginCalled(false)
{
}

FTPTask::~FTPTask()
{
}

bool FTPTask::setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig)
{
	_ftpServer = std::shared_ptr<FTPServer>(new FTPServer());
	if(config->ftp.active)
	{
		for(Configuration::Ftp::User user : config->ftp.users)
		{
			logPrintD("Adding user to FTP Server: ");
			logPrintlnD(user.name);
			_ftpServer->addUser(user.name, user.password);
		}
		_ftpServer->addFilesystem("SPIFFS", &SPIFFS);
	}
	return true;
}

bool FTPTask::loop(std::shared_ptr<Configuration> config)
{
	if(config->ftp.active)
	{
		if(!_beginCalled)
		{
			_ftpServer->begin();
			_beginCalled = true;
		}
		_ftpServer->handle();
		static bool configWasOpen = false;
		if(configWasOpen && _ftpServer->countConnections() == 0)
		{
			logPrintlnW("Maybe the config has been changed via FTP, lets restart now to get the new config...");
			logPrintlnW("");
			ESP.restart();
		}
		if(_ftpServer->countConnections() > 0)
		{
			configWasOpen = true;
		}
	}
	return true;
}
