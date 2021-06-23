#ifndef TASK_WIFI_H_
#define TASK_WIFI_H_

#include <TaskManager.h>
#include <WiFiMulti.h>

class WifiTask : public Task {
public:
  WifiTask();
  virtual ~WifiTask();

  virtual bool setup(System &system) override;
  virtual bool loop(System &system) override;

private:
  WiFiMulti _wiFiMulti;
  uint8_t   _oldWifiStatus;
};

#endif
