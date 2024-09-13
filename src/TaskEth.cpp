#include <ETH.h>
#include <WiFi.h>
#include <logger.h>

#include "Task.h"
#include "TaskEth.h"
#include "project_configuration.h"

#define WIFI_EVENT "WiFiEvent"

volatile bool    eth_connected = false;
logging::Logger *_logger;

void setWiFiLogger(logging::Logger *logger) {
  _logger = logger;
}

void WiFiEvent(WiFiEvent_t event) {
  switch (event) {
  case ARDUINO_EVENT_WIFI_STA_START:
    _logger->log(logging::LoggerLevel::LOGGER_LEVEL_INFO, WIFI_EVENT, "WiFi Started");
    break;
  case ARDUINO_EVENT_WIFI_STA_CONNECTED:
    _logger->log(logging::LoggerLevel::LOGGER_LEVEL_INFO, WIFI_EVENT, "WiFi Connected");
    break;
  case ARDUINO_EVENT_WIFI_STA_GOT_IP:
    _logger->log(logging::LoggerLevel::LOGGER_LEVEL_INFO, WIFI_EVENT, "WiFi MAC: %s", WiFi.macAddress().c_str());
    _logger->log(logging::LoggerLevel::LOGGER_LEVEL_INFO, WIFI_EVENT, "WiFi IPv4: %s", WiFi.localIP().toString().c_str());
    _logger->log(logging::LoggerLevel::LOGGER_LEVEL_INFO, WIFI_EVENT, "WiFi Gateway: %s", WiFi.gatewayIP().toString().c_str());
    _logger->log(logging::LoggerLevel::LOGGER_LEVEL_INFO, WIFI_EVENT, "WiFi DNS1: %s", WiFi.dnsIP().toString().c_str());
    _logger->log(logging::LoggerLevel::LOGGER_LEVEL_INFO, WIFI_EVENT, "WiFi DNS2: %s", WiFi.dnsIP(1).toString().c_str());
    _logger->log(logging::LoggerLevel::LOGGER_LEVEL_INFO, WIFI_EVENT, "WiFi Hostname: %s", WiFi.getHostname());
    break;
  case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
    _logger->log(logging::LoggerLevel::LOGGER_LEVEL_INFO, WIFI_EVENT, "WiFi Disconnected");
    break;
  case ARDUINO_EVENT_WIFI_STA_STOP:
    _logger->log(logging::LoggerLevel::LOGGER_LEVEL_INFO, WIFI_EVENT, "WiFi Stopped");
    break;
  case ARDUINO_EVENT_ETH_START:
    _logger->log(logging::LoggerLevel::LOGGER_LEVEL_INFO, WIFI_EVENT, "ETH Started");
    break;
  case ARDUINO_EVENT_ETH_CONNECTED:
    _logger->log(logging::LoggerLevel::LOGGER_LEVEL_INFO, WIFI_EVENT, "ETH Connected");
    break;
  case ARDUINO_EVENT_ETH_GOT_IP:
    _logger->log(logging::LoggerLevel::LOGGER_LEVEL_INFO, WIFI_EVENT, "ETH MAC: %s", ETH.macAddress().c_str());
    _logger->log(logging::LoggerLevel::LOGGER_LEVEL_INFO, WIFI_EVENT, "ETH IPv4: %s", ETH.localIP().toString().c_str());
    _logger->log(logging::LoggerLevel::LOGGER_LEVEL_INFO, WIFI_EVENT, "ETH Gateway: %s", ETH.gatewayIP().toString().c_str());
    _logger->log(logging::LoggerLevel::LOGGER_LEVEL_INFO, WIFI_EVENT, "ETH DNS1: %s", ETH.dnsIP().toString().c_str());
    _logger->log(logging::LoggerLevel::LOGGER_LEVEL_INFO, WIFI_EVENT, "ETH DNS2: %s", ETH.dnsIP(1).toString().c_str());
    _logger->log(logging::LoggerLevel::LOGGER_LEVEL_INFO, WIFI_EVENT, "ETH Hostname: %s", ETH.getHostname());
    if (ETH.fullDuplex()) {
      _logger->log(logging::LoggerLevel::LOGGER_LEVEL_INFO, WIFI_EVENT, "ETH FULL_DUPLEX");
    }
    _logger->log(logging::LoggerLevel::LOGGER_LEVEL_INFO, WIFI_EVENT, "ETH Speed: %dMbps", ETH.linkSpeed());
    eth_connected = true;
    break;
  case ARDUINO_EVENT_ETH_DISCONNECTED:
    _logger->log(logging::LoggerLevel::LOGGER_LEVEL_WARN, WIFI_EVENT, "ETH Disconnected");
    eth_connected = false;
    break;
  case ARDUINO_EVENT_ETH_STOP:
    _logger->log(logging::LoggerLevel::LOGGER_LEVEL_WARN, WIFI_EVENT, "ETH Stopped");
    eth_connected = false;
    break;
  default:
    break;
  }
}

EthTask::EthTask() : Task(TASK_ETH, TaskEth) {
}

EthTask::~EthTask() {
}

bool EthTask::setup(System &system) {
  WiFi.onEvent(WiFiEvent);

#ifdef T_INTERNET_POE
  if (ETH_NRESET != -1) {
    pinMode(ETH_NRESET, OUTPUT);
    digitalWrite(ETH_NRESET, 0);
    delay(200);
    digitalWrite(ETH_NRESET, 1);
    delay(200);
    digitalWrite(ETH_NRESET, 0);
    delay(200);
    digitalWrite(ETH_NRESET, 1);
  }

  ETH.begin(ETH_ADDR, ETH_POWER, ETH_MDC, ETH_MDIO, (eth_phy_type_t)ETH_TYPE, (eth_clock_mode_t)ETH_CLOCK);

  if (!system.getUserConfig()->network.DHCP) {
    ETH.config(system.getUserConfig()->network.static_.ip, system.getUserConfig()->network.static_.gateway, system.getUserConfig()->network.static_.subnet, system.getUserConfig()->network.static_.dns1, system.getUserConfig()->network.static_.dns2);
  }
  if (system.getUserConfig()->network.hostname.overwrite) {
    ETH.setHostname(system.getUserConfig()->network.hostname.name.c_str());
  } else {
    ETH.setHostname(system.getUserConfig()->callsign.c_str());
  }
#endif

  return true;
}

bool EthTask::loop(System &system) {
  if (!eth_connected) {
    system.connectedViaEth(false);
    _stateInfo = "Ethernet not connected";
    _state     = Error;
    return false;
  }
  system.connectedViaEth(true);
  _stateInfo = ETH.localIP().toString();
  _state     = Okay;
  return true;
}
