#include <logger.h>

#include "Task.h"
#include "TaskMQTT.h"
#include "project_configuration.h"

#include <ArduinoJson.h>

MQTTTask::MQTTTask(TaskQueue<std::shared_ptr<APRSMessage>> &toMQTT) : Task(TASK_MQTT, TaskMQTT), _toMQTT(toMQTT), _MQTT(_client) {
}

MQTTTask::~MQTTTask() {
}

bool MQTTTask::setup(System &system) {
  _MQTT.setServer(system.getUserConfig()->mqtt.server.c_str(), system.getUserConfig()->mqtt.port);
  return true;
}

bool MQTTTask::loop(System &system) {
  if (!system.isWifiEthConnected()) {
    return false;
  }

  if (!_MQTT.connected()) {
    connect(system);
  }

  if (!_toMQTT.empty()) {
    std::shared_ptr<APRSMessage> msg = _toMQTT.getElement();

    DynamicJsonDocument data(1024);
    data["Source"]      = msg->getSource();
    data["Destination"] = msg->getDestination();
    data["Path"]        = msg->getPath();
    data["Type"]        = msg->getType().toString();
    String body         = msg->getBody()->encode();
    body.replace("\n", "");
    data["Data"] = body;

    String r;
    serializeJson(data, r);

    String topic = String(system.getUserConfig()->mqtt.topic);
    if (!topic.endsWith("/")) {
      topic = topic + "/";
    }
    topic = topic + system.getUserConfig()->callsign;

    logPrintD("Send MQTT with topic: \"");
    logPrintD(topic);
    logPrintD("\", data: ");
    logPrintlnD(r);

    _MQTT.publish(topic.c_str(), r.c_str());
  }
  _MQTT.loop();
  return true;
}

bool MQTTTask::connect(const System &system) {
  logPrintI("Connecting to MQTT broker: ");
  logPrintI(system.getUserConfig()->mqtt.server);
  logPrintI(" on port ");
  logPrintlnI(String(system.getUserConfig()->mqtt.port));

  if (_MQTT.connect(system.getUserConfig()->callsign.c_str(), system.getUserConfig()->mqtt.name.c_str(), system.getUserConfig()->mqtt.password.c_str())) {
    logPrintI("Connected to MQTT broker as: ");
    logPrintlnI(system.getUserConfig()->callsign);
    return true;
  }
  logPrintlnI("Connecting to MQTT broker faild. Try again later.");
  return false;
}
