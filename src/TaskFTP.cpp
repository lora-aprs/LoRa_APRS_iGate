#include <FTPFilesystem.h>
#include <SPIFFS.h>
#include <logger.h>

#include "Task.h"
#include "TaskFTP.h"
#include "project_configuration.h"

FTPTask::FTPTask() : Task(TASK_FTP, TaskFtp), _beginCalled(false) {
}

FTPTask::~FTPTask() {
}

bool FTPTask::setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig) {
  _ftpServer = std::shared_ptr<FTPServer>(new FTPServer());
  for (Configuration::Ftp::User user : config->ftp.users) {
    logPrintD("Adding user to FTP Server: ");
    logPrintlnD(user.name);
    _ftpServer->addUser(user.name, user.password);
  }
  _ftpServer->addFilesystem("SPIFFS", &SPIFFS);
  _stateInfo = "waiting";
  return true;
}

bool FTPTask::loop(std::shared_ptr<Configuration> config) {
  if (!_beginCalled) {
    _ftpServer->begin();
    _beginCalled = true;
  }
  _ftpServer->handle();
  static bool configWasOpen = false;
  if (configWasOpen && _ftpServer->countConnections() == 0) {
    logPrintlnW("Maybe the config has been changed via FTP, lets restart now to get the new config...");
    logPrintlnW("");
    ESP.restart();
  }
  if (_ftpServer->countConnections() > 0) {
    configWasOpen = true;
    _stateInfo    = "has connection";
  }
  return true;
}
