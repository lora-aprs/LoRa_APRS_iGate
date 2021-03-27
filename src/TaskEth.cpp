#include <ETH.h>
#include <WiFi.h>
#include <logger.h>

#include "Task.h"
#include "TaskEth.h"

volatile bool eth_connected = false;

static void WiFiEvent(WiFiEvent_t event) {
  switch (event) {
  case SYSTEM_EVENT_ETH_START:
    logPrintlnI("ETH Started");
    ETH.setHostname("esp32-ethernet");
    break;
  case SYSTEM_EVENT_ETH_CONNECTED:
    logPrintlnI("ETH Connected");
    break;
  case SYSTEM_EVENT_ETH_GOT_IP:
    logPrintI("ETH MAC: ");
    logPrintI(ETH.macAddress());
    logPrintI(", IPv4: ");
    logPrintI(ETH.localIP().toString());
    if (ETH.fullDuplex()) {
      logPrintI(", FULL_DUPLEX");
    }
    logPrintI(", ");
    logPrintI(String(ETH.linkSpeed()));
    logPrintlnI("Mbps");
    eth_connected = true;
    break;
  case SYSTEM_EVENT_ETH_DISCONNECTED:
    logPrintlnW("ETH Disconnected");
    eth_connected = false;
    break;
  case SYSTEM_EVENT_ETH_STOP:
    logPrintlnW("ETH Stopped");
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

bool EthTask::setup(std::shared_ptr<System> system) {
  WiFi.onEvent(WiFiEvent);

  constexpr uint8_t          ETH_NRST      = 5;
  constexpr uint8_t          ETH_ADDR      = 0;
  constexpr int              ETH_POWER_PIN = -1;
  constexpr int              ETH_MDC_PIN   = 23;
  constexpr int              ETH_MDIO_PIN  = 18;
  constexpr eth_phy_type_t   ETH_TYPE      = ETH_PHY_LAN8720;
  constexpr eth_clock_mode_t ETH_CLK       = ETH_CLOCK_GPIO17_OUT; // TTGO PoE V1.0
  // constexpr eth_clock_mode_t ETH_CLK       = ETH_CLOCK_GPIO0_OUT;  // TTGO PoE V1.2

  pinMode(ETH_NRST, OUTPUT);
  digitalWrite(ETH_NRST, 0);
  delay(200);
  digitalWrite(ETH_NRST, 1);
  delay(200);
  digitalWrite(ETH_NRST, 0);
  delay(200);
  digitalWrite(ETH_NRST, 1);

  ETH.begin(ETH_ADDR, ETH_POWER_PIN, ETH_MDC_PIN, ETH_MDIO_PIN, ETH_TYPE, ETH_CLK);
  return true;
}

bool EthTask::loop(std::shared_ptr<System> system) {
  if (!eth_connected) {
    system->connectedViaWifiEth(false);
    _stateInfo = "Ethernet not connected";
    _state     = Error;
    return false;
  }
  system->connectedViaWifiEth(true);
  _stateInfo = ETH.localIP().toString();
  _state     = Okay;
  return true;
}
