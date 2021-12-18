#include <WiFi.h>
#include <logger.h>

#include "Task.h"
#include "TaskEth.h"
#include "TaskWifi.h"
#include "project_configuration.h"

WifiTask::WifiTask() : Task(TASK_WIFI, TaskWifi), _oldWifiStatus(WL_IDLE_STATUS) {
}

WifiTask::~WifiTask() {
}

bool WifiTask::setup(System &system) {
  // Don't save WiFi configuration in flash
  WiFi.persistent(false);

  // Set WiFi to station mode
  WiFi.mode(WIFI_STA);

  WiFi.onEvent(WiFiEvent);
  if (system.getUserConfig()->network.hostname.overwrite) {
    WiFi.setHostname(system.getUserConfig()->network.hostname.name.c_str());
  } else {
    WiFi.setHostname(system.getUserConfig()->callsign.c_str());
  }

  if (!system.getUserConfig()->network.DHCP) {
    WiFi.config(system.getUserConfig()->network.static_.ip, system.getUserConfig()->network.static_.gateway, system.getUserConfig()->network.static_.subnet, system.getUserConfig()->network.static_.dns1, system.getUserConfig()->network.static_.dns2);
  }

  for (Configuration::Wifi::AP ap : system.getUserConfig()->wifi.APs) {
    logPrintD("Looking for AP: ");
    logPrintlnD(ap.SSID);
    _wiFiMulti.addAP(ap.SSID.c_str(), ap.password.c_str());
  }
  return true;
}

bool WifiTask::loop(System &system) {
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
