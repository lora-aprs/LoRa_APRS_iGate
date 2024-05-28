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
  if (!system.isWifiOrEthConnected()) {
    return false;
  }

  if (!_MQTT.connected()) {
    connect(system);
  }

  if (!_toMQTT.empty()) {
    std::shared_ptr<APRSMessage> msg = _toMQTT.getElement();

    DynamicJsonDocument data(1024);
    data["source"]      = msg->getSource();
    data["destination"] = msg->getDestination();
    data["path"]        = msg->getPath();
    data["type"]        = msg->getType().toString();
    String body         = msg->getBody()->encode();
    body.replace("\n", "");
    data["data"] = body;

    String r;
    serializeJson(data, r);

    String topic = String(system.getUserConfig()->mqtt.topic);
    if (!topic.endsWith("/")) {
      topic = topic + "/";
    }
    topic = topic + system.getUserConfig()->callsign;
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_DEBUG, getName(), "Send MQTT with topic: '%s', data: %s", topic.c_str(), r.c_str());
    _MQTT.publish(topic.c_str(), r.c_str());
  }
  _MQTT.loop();
  return true;
}

bool MQTTTask::connect(System &system) {
  bool result = false;
  system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, getName(), "Connecting to MQTT broker: %s on port %d", system.getUserConfig()->mqtt.server.c_str(), system.getUserConfig()->mqtt.port);
  if (system.getUserConfig()->mqtt.will_active) {
    result = _MQTT.connect(system.getUserConfig()->callsign.c_str(), system.getUserConfig()->mqtt.name.c_str(), system.getUserConfig()->mqtt.password.c_str(), system.getUserConfig()->mqtt.will_topic.c_str(), 0, true, system.getUserConfig()->mqtt.will_message.c_str());
  } else {
    result = _MQTT.connect(system.getUserConfig()->callsign.c_str(), system.getUserConfig()->mqtt.name.c_str(), system.getUserConfig()->mqtt.password.c_str());
  }
  if (result) {
    system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, getName(), "Connected to MQTT broker as: %s", system.getUserConfig()->callsign.c_str());
    if (system.getUserConfig()->mqtt.will_active) {
      system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, getName(), "Sending birth message to MQTT.");
      _MQTT.publish(system.getUserConfig()->mqtt.will_topic.c_str(), system.getUserConfig()->mqtt.birth_message.c_str(), true);
    }
    return true;
  }
  system.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, getName(), "Connecting to MQTT broker failed. Try again later.");
  return false;
}
