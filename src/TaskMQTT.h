#ifndef TASK_MQTT_H_
#define TASK_MQTT_H_

#include <APRSMessage.h>
#include <PubSubClient.h>
#include <TaskManager.h>

class MQTTTask : public Task {
public:
  MQTTTask(TaskQueue<std::shared_ptr<APRSMessage>> &toMQTT);
  virtual ~MQTTTask();

  virtual bool setup(System &system) override;
  virtual bool loop(System &system) override;

private:
  TaskQueue<std::shared_ptr<APRSMessage>> &_toMQTT;

  WiFiClient   _client;
  PubSubClient _MQTT;

  bool connect(const System &system);
};

#endif
