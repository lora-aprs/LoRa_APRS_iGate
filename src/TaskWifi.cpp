#include <WiFi.h>
#include <logger.h>

#include "Task.h"
#include "TaskEth.h"
#include "TaskWifi.h"
#include "configuration.h"

WifiTask::WifiTask() : Task(TASK_WIFI, TaskWifi), _oldWifiStatus(WL_IDLE_STATUS), _isAPMode(false) {
}

WifiTask::~WifiTask() {
}

bool WifiTask::setup(System &system) {
  WiFi.onEvent(WiFiEvent);
  WiFi.setHostname(system.getUserConfig()->callsign().c_str());
  if (system.getUserConfig()->wifi.ssid() == "" && system.getUserConfig()->wifi.password() == "") {
    // ssid and password not set...
    WiFi.softAP("LoRa APRS iGate", "LoRaAPRS");
    IPAddress IP = WiFi.softAPIP();
    logPrintD("AP IP address: ");
    logPrintlnD(IP.toString());
    _isAPMode = true;
    system.connectedViaWifiEth(true);
  } else {
    logPrintD("Looking for AP: ");
    logPrintlnD(system.getUserConfig()->wifi.ssid());
    _wiFiMulti.addAP(system.getUserConfig()->wifi.ssid().c_str(), system.getUserConfig()->wifi.password().c_str());
  }
  return true;
}

bool WifiTask::loop(System &system) {
  if (_isAPMode) {
    return false;
  }
  const uint8_t wifi_status = _wiFiMulti.run();
  if (wifi_status != WL_CONNECTED) {
    system.connectedViaWifiEth(false);
    logPrintlnE("WiFi not connected!");
    _oldWifiStatus = wifi_status;
    _stateInfo     = "WiFi not connected";
    _state         = Error;
    return false;
  } else if (wifi_status != _oldWifiStatus) {
    logPrintD("IP address: ");
    logPrintlnD(WiFi.localIP().toString());
    _oldWifiStatus = wifi_status;
    return false;
  }
  system.connectedViaWifiEth(true);
  _stateInfo = WiFi.localIP().toString();
  _state     = Okay;
  return true;
}
