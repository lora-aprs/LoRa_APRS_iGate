#include <logger.h>

#include "Task.h"
#include "TaskMQTT.h"
#include "project_configuration.h"

#include <WiFi.h>
#include <WiFiMulti.h>

#include <ArduinoJson.h>

WiFiClient wiFiClient;
PubSubClient _MQTT(wiFiClient);


MQTTTask::MQTTTask(TaskQueue<std::shared_ptr<APRSMessage>> &toMQTT) : Task(TASK_MQTT, TaskMQTT), _beginCalled(false), _toMQTT(toMQTT) {
}

MQTTTask::~MQTTTask() {
}

bool MQTTTask::setup(System &system) { 
  _MQTT.setServer(system.getUserConfig()->mqtt.server.c_str(), system.getUserConfig()->mqtt.port);

  return true;
}

bool MQTTTask::loop(System &system) {
  if (!_beginCalled) {
    _beginCalled = true;
  }

  if (!system.isWifiEthConnected()) {
    return false;
  }
  
  if (!_MQTT.connected()) {
    connect(system);
  }

  if (!_toMQTT.empty()) {
    std::shared_ptr<APRSMessage> msg = _toMQTT.getElement();

    DynamicJsonDocument _Data(1024);
    String _r;

    _Data["Source"] = msg->getSource();
    _Data["Destination"] = msg->getDestination();
    _Data["Path"] = msg->getPath();
    _Data["Type"] = msg->getType().toString();
    String _body = msg->getBody()->encode();
    _body.replace("\n", "");
    _Data["Data"] = _body;

    serializeJson(_Data, _r);

    logPrintD("Send MQTT: ");
    logPrintlnD(_r);
    
    String _topic = String(system.getUserConfig()->mqtt.topic);

    if (!_topic.endsWith("/")) {
      _topic = _topic + "/";
    }
    _topic = _topic + system.getUserConfig()->callsign;

    _MQTT.publish(_topic.c_str(), _r.c_str());
  }
  _MQTT.loop();
  return true;
}

bool MQTTTask::connect(const System &system) {
  logPrintI("Connecting to MQTT broker: ");  
  logPrintI(system.getUserConfig()->mqtt.server);
  logPrintI(" on port ");  
  logPrintlnI(String(system.getUserConfig()->mqtt.port));
    
  if (_MQTT.connect(system.getUserConfig()->callsign.c_str(),system.getUserConfig()->mqtt.name.c_str() ,system.getUserConfig()->mqtt.password.c_str() )) {
    logPrintI("Connected to MQTT broker as: ");  
    logPrintlnI(system.getUserConfig()->callsign);

    return true;
  } else {
    logPrintlnI("Connecting to MQTT broker faild. Try again later.");  
  } 
  return false;
}
