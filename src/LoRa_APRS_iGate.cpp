#ifndef UNIT_TEST
#include <map>

#include <esp_task_wdt.h>
#include <logger.h>

#include "APRS-IS/APRS-IS.h"
#include "Board.h"
#include "PowerManagement/power_management.h"
#include "System/System.h"
#include "System/TaskManager.h"

#include "TaskAprsIs.h"
#include "TaskBeacon.h"
#include "TaskDisplay.h"
#include "TaskEth.h"
#include "TaskFTP.h"
#include "TaskMQTT.h"
#include "TaskNTP.h"
#include "TaskOTA.h"
#include "TaskRadiolib.h"
#include "TaskRouter.h"
#include "TaskWifi.h"
#include "project_configuration.h"

#define VERSION     "23.31.01"
#define MODULE_NAME "Main"

String create_lat_aprs(double lat);
String create_long_aprs(double lng);

TaskQueue<std::shared_ptr<APRSMessage>> toAprsIs;
TaskQueue<std::shared_ptr<APRSMessage>> fromModem;
TaskQueue<std::shared_ptr<APRSMessage>> toModem;
TaskQueue<std::shared_ptr<APRSMessage>> toMQTT;

System        LoRaSystem;
Configuration userConfig;

#ifdef HAS_AXP192
AXP192           axp;
PowerManagement *powerManagement = &axp;
#endif
#ifdef HAS_AXP2101
AXP2101          axp;
PowerManagement *powerManagement = &axp;
#endif

DisplayTask displayTask;
//  ModemTask   modemTask(fromModem, toModem);
RadiolibTask modemTask(fromModem, toModem);
EthTask      ethTask;
WifiTask     wifiTask;
OTATask      otaTask;
NTPTask      ntpTask;
FTPTask      ftpTask;
MQTTTask     mqttTask(toMQTT);
AprsIsTask   aprsIsTask(toAprsIs, toModem);
RouterTask   routerTask(fromModem, toModem, toAprsIs, toMQTT);
BeaconTask   beaconTask(toModem, toAprsIs);

void setup() {
  Serial.begin(115200);
  LoRaSystem.getLogger().setSerial(&Serial);
  setWiFiLogger(&LoRaSystem.getLogger());
  delay(1000);
  LoRaSystem.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, MODULE_NAME, "LoRa APRS iGate by OE5BPA (Peter Buchegger)");
  LoRaSystem.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, MODULE_NAME, "Version: %s", VERSION);
  LoRaSystem.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, MODULE_NAME, "Board: %s", getBoardName().c_str());

  ProjectConfigurationManagement confmg(LoRaSystem.getLogger());
  confmg.readConfiguration(LoRaSystem.getLogger(), userConfig);

  LoRaSystem.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, MODULE_NAME, "Will start watchdog now...");
  if (esp_task_wdt_init(10, true) != ESP_OK) {
    LoRaSystem.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_WARN, MODULE_NAME, "Watchdog init failed!");
  } else {
    if (esp_task_wdt_add(NULL) != ESP_OK) {
      LoRaSystem.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_WARN, MODULE_NAME, "Watchdog add failed!");
    }
  }

#if defined(HAS_AXP192) || defined(HAS_AXP2101)
  Wire.begin(SDA, SCL);
  if (powerManagement->begin(Wire)) {
    LoRaSystem.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, "PMU", "init done!");
  } else {
    LoRaSystem.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, "PMU", "init failed!");
  }
  powerManagement->activateLoRa();
  powerManagement->activateOLED();
  if (userConfig.beacon.use_gps) {
    powerManagement->activateGPS();
  } else {
    powerManagement->deactivateGPS();
  }
  // powerManagement->activateMeasurement();
#endif

  LoRaSystem.setUserConfig(&userConfig);
  LoRaSystem.getTaskManager().addTask(&displayTask);
  LoRaSystem.getTaskManager().addTask(&modemTask);
  LoRaSystem.getTaskManager().addTask(&routerTask);
  LoRaSystem.getTaskManager().addTask(&beaconTask);

  bool tcpip = false;

  if (userConfig.wifi.active) {
    LoRaSystem.getTaskManager().addAlwaysRunTask(&wifiTask);
    tcpip = true;
  }

#ifdef T_INTERNET_POE
  LoRaSystem.getTaskManager().addAlwaysRunTask(&ethTask);
  tcpip = true; // cppcheck-suppress redundantAssignment
#endif

  if (tcpip) { // cppcheck-suppress knownConditionTrueFalse
    LoRaSystem.getTaskManager().addTask(&otaTask);
    LoRaSystem.getTaskManager().addTask(&ntpTask);
    if (userConfig.ftp.active) {
      LoRaSystem.getTaskManager().addTask(&ftpTask);
    }

    if (userConfig.aprs_is.active) {
      LoRaSystem.getTaskManager().addTask(&aprsIsTask);
    }

    if (userConfig.mqtt.active) {
      LoRaSystem.getTaskManager().addTask(&mqttTask);
    }
  }

  esp_task_wdt_reset();
  LoRaSystem.getTaskManager().setup(LoRaSystem);

  LoRaSystem.getDisplay().showSpashScreen("LoRa APRS iGate", VERSION, getBoardName());

  if (userConfig.callsign == "NOCALL-10") {
    LoRaSystem.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, MODULE_NAME, "You have to change your settings in 'data/is-cfg.json' and upload it via 'Upload File System image'!");
    LoRaSystem.getDisplay().showStatusScreen("ERROR", "You have to change your settings in 'data/is-cfg.json' and upload it via \"Upload File System image\"!");
    while (true) {
      esp_task_wdt_reset();
    }
  }
  if ((!userConfig.aprs_is.active) && !(userConfig.digi.active)) {
    LoRaSystem.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, MODULE_NAME, "No mode selected (iGate or Digi)! You have to activate one of iGate or Digi.");
    LoRaSystem.getDisplay().showStatusScreen("ERROR", "No mode selected (iGate or Digi)! You have to activate one of iGate or Digi.");
    while (true)
      ;
  }

  if (userConfig.display.overwritePin != 0) {
    pinMode(userConfig.display.overwritePin, INPUT);
    pinMode(userConfig.display.overwritePin, INPUT_PULLUP);
  }

  LoRaSystem.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, MODULE_NAME, "setup done...");
}

volatile bool syslogSet = false;

void loop() {
  esp_task_wdt_reset();
  LoRaSystem.getTaskManager().loop(LoRaSystem);
  if (LoRaSystem.isWifiOrEthConnected() && LoRaSystem.getUserConfig()->syslog.active && !syslogSet) {
    LoRaSystem.getLogger().setSyslogServer(LoRaSystem.getUserConfig()->syslog.server, LoRaSystem.getUserConfig()->syslog.port, LoRaSystem.getUserConfig()->callsign);
    LoRaSystem.getLogger().log(logging::LoggerLevel::LOGGER_LEVEL_INFO, MODULE_NAME, "System connected after a restart to the network, syslog server set");
    syslogSet = true;
  }
}

#endif
