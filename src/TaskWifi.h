#ifndef TASK_WIFI_H_
#define TASK_WIFI_H_

#include <TaskManager.h>
#include <WiFiMulti.h>

class WifiTask : public Task {
public:
  WifiTask();
  virtual ~WifiTask();

  virtual bool setup(std::shared_ptr<System> system) override;
  virtual bool loop(std::shared_ptr<System> system) override;

private:
  std::shared_ptr<WiFiMulti> _wiFiMulti;
  uint8_t                    _oldWifiStatus;
};

#endif
