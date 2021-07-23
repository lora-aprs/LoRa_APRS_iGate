#include <map>

#include <APRS-IS.h>
#include <BoardFinder.h>
#include <System.h>
#include <TaskManager.h>
#include <logger.h>
#include <power_management.h>

#include "TaskAprsIs.h"
#include "TaskDisplay.h"
#include "TaskEth.h"
#include "TaskFTP.h"
#include "TaskModem.h"
#include "TaskNTP.h"
#include "TaskOTA.h"
#include "TaskRouter.h"
#include "TaskWifi.h"
#include "configuration.h"

#define VERSION "21.25.0-dev"

String create_lat_aprs(double lat);
String create_long_aprs(double lng);

TaskQueue<std::shared_ptr<APRSMessage>> toAprsIs;
TaskQueue<std::shared_ptr<APRSMessage>> fromModem;
TaskQueue<std::shared_ptr<APRSMessage>> toModem;

System         LoRaSystem;
Configuration  userConfig;
ConfigHTML     html;
ConfigFactory  fact;
const String   config_filename = "/is-cfg.json";
AsyncWebServer server(80);

DisplayTask displayTask;
ModemTask   modemTask(fromModem, toModem);
EthTask     ethTask;
WifiTask    wifiTask;
OTATask     otaTask;
NTPTask     ntpTask;
FTPTask     ftpTask;
AprsIsTask  aprsIsTask(toAprsIs);
RouterTask  routerTask(fromModem, toModem, toAprsIs);

void setup() {
  Serial.begin(115200);
  Logger::instance().setSerial(&Serial);
  SPIFFS.begin(true);
  delay(500);
  logPrintlnI("LoRa APRS iGate by OE5BPA (Peter Buchegger)");
  logPrintlnI("Version: " VERSION);

  std::list<BoardConfig const *> boardConfigs;
  boardConfigs.push_back(&TTGO_LORA32_V1);
  boardConfigs.push_back(&TTGO_LORA32_V2);
  boardConfigs.push_back(&TTGO_T_Beam_V0_7);
  boardConfigs.push_back(&TTGO_T_Beam_V1_0);
  boardConfigs.push_back(&ETH_BOARD);
  boardConfigs.push_back(&TRACKERD);
  boardConfigs.push_back(&HELTEC_WIFI_LORA_32_V1);
  boardConfigs.push_back(&HELTEC_WIFI_LORA_32_V2);

  fact.addPage(&page);
  fact.loadConfig(config_filename);

  html.addPage(&page);
  html.registerWebServer(server);
  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
  });

  BoardFinder        finder(boardConfigs);
  BoardConfig const *boardConfig = finder.getBoardConfig(userConfig.board());
  if (!boardConfig) {
    boardConfig = finder.searchBoardConfig();
    if (!boardConfig) {
      logPrintlnE("Board config not set and search failed!");
      while (true)
        ;
    } else {
      userConfig.board.setValue(boardConfig->Name);
      fact.saveConfig(config_filename);
      logPrintlnI("will restart board now!");
      ESP.restart();
    }
  }

  logPrintI("Board ");
  logPrintI(boardConfig->Name);
  logPrintlnI(" loaded.");

  if (boardConfig->Type == eTTGO_T_Beam_V1_0) {
    Wire.begin(boardConfig->OledSda, boardConfig->OledScl);
    PowerManagement powerManagement;
    if (!powerManagement.begin(Wire)) {
      logPrintlnI("AXP192 init done!");
    } else {
      logPrintlnE("AXP192 init failed!");
    }
    powerManagement.activateLoRa();
    powerManagement.activateOLED();
    powerManagement.deactivateGPS();
  }

  LoRaSystem.setBoardConfig(boardConfig);
  LoRaSystem.setUserConfig(&userConfig);
  LoRaSystem.getTaskManager().addTask(&displayTask);
  if (userConfig.callsign() != "NOCALL-10") {
    LoRaSystem.getTaskManager().addTask(&modemTask);
    LoRaSystem.getTaskManager().addTask(&routerTask);
  }

  if (userConfig.aprs_is.active()) {
    if (boardConfig->Type == eETH_BOARD) {
      LoRaSystem.getTaskManager().addAlwaysRunTask(&ethTask);
    } else {
      LoRaSystem.getTaskManager().addAlwaysRunTask(&wifiTask);
    }
    LoRaSystem.getTaskManager().addTask(&otaTask);
    LoRaSystem.getTaskManager().addTask(&ntpTask);
    if (userConfig.ftp.active()) {
      LoRaSystem.getTaskManager().addTask(&ftpTask);
    }
    if (userConfig.callsign() != "NOCALL-10") {
      LoRaSystem.getTaskManager().addTask(&aprsIsTask);
    }
  }

  LoRaSystem.getTaskManager().setup(LoRaSystem);

  LoRaSystem.getDisplay().showSpashScreen("LoRa APRS iGate", VERSION);

  if (userConfig.display.overwritePin() != 0) {
    pinMode(userConfig.display.overwritePin(), INPUT);
    pinMode(userConfig.display.overwritePin(), INPUT_PULLUP);
  }

  delay(5000);
  logPrintlnI("setup done...");
}

void loop() {
  LoRaSystem.getTaskManager().loop(LoRaSystem);
  if (html.wasSaved()) {
    fact.saveConfig(config_filename);
    ESP.restart();
  }

  // we can start the http server just when we are connected to something
  static bool httpServerInitDone = false;
  if (LoRaSystem.isWifiEthConnected() && !httpServerInitDone) {
    server.begin();
    httpServerInitDone = true;
  }
}

String create_lat_aprs(double lat) {
  char str[20];
  char n_s = 'N';
  if (lat < 0) {
    n_s = 'S';
  }
  lat = std::abs(lat);
  sprintf(str, "%02d%05.2f%c", (int)lat, (lat - (double)((int)lat)) * 60.0, n_s);
  String lat_str(str);
  return lat_str;
}

String create_long_aprs(double lng) {
  char str[20];
  char e_w = 'E';
  if (lng < 0) {
    e_w = 'W';
  }
  lng = std::abs(lng);
  sprintf(str, "%03d%05.2f%c", (int)lng, (lng - (double)((int)lng)) * 60.0, e_w);
  String lng_str(str);
  return lng_str;
}
