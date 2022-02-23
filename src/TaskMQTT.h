#ifndef TASK_MQTT_H_
#define TASK_MQTT_H_

#include <APRSMessage.h>
#include <TaskManager.h>
#include <PubSubClient.h>

class MQTTTask : public Task {
public:
  MQTTTask(TaskQueue<std::shared_ptr<APRSMessage>> &toMQTT);
  virtual ~MQTTTask();

  virtual bool setup(System &system) override;
  virtual bool loop(System &system) override;
  
private:
  bool      _beginCalled;
  TaskQueue<std::shared_ptr<APRSMessage>> &_toMQTT;  
  bool connect(const System &system);  
};

#endif
