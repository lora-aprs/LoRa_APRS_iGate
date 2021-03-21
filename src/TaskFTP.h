#ifndef TASK_FTP_H_
#define TASK_FTP_H_

#include <ESP-FTP-Server-Lib.h>
#include <TaskManager.h>

class FTPTask : public Task {
public:
  FTPTask();
  virtual ~FTPTask();

  virtual bool setup(std::shared_ptr<System> system) override;
  virtual bool loop(std::shared_ptr<System> system) override;

private:
  std::shared_ptr<FTPServer> _ftpServer;
  bool                       _beginCalled;
};

#endif
