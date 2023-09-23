#ifndef TASK_FTP_H_
#define TASK_FTP_H_

#include "System/TaskManager.h"
#include <ESP-FTP-Server-Lib.h>

class FTPTask : public Task {
public:
  FTPTask();
  virtual ~FTPTask();

  virtual bool setup(System &system) override;
  virtual bool loop(System &system) override;

private:
  FTPServer _ftpServer;
  bool      _beginCalled;
};

#endif
