#include "BoardFinder.h"
#include <logger.h>
#include <power_management.h>

#define MODULE_NAME "BoardFinder"

BoardConfig::BoardConfig(String name, BoardType type, uint8_t oledsda, uint8_t oledscl, uint8_t oledaddr, uint8_t oledreset, uint8_t lorasck, uint8_t loramiso, uint8_t loramosi, uint8_t loracs, uint8_t lorareset, uint8_t lorairq, uint8_t gpsrx, uint8_t gpstx, uint8_t button, bool needcheckpowerchip, bool powercheckstatus)
    : Name(name), Type(type), OledSda(oledsda), OledScl(oledscl), OledAddr(oledaddr), OledReset(oledreset), LoraSck(lorasck), LoraMiso(loramiso), LoraMosi(loramosi), LoraCS(loracs), LoraReset(lorareset), LoraIRQ(lorairq), GpsRx(gpsrx), GpsTx(gpstx), Button(button), needCheckPowerChip(needcheckpowerchip), powerCheckStatus(powercheckstatus) {
}

BoardFinder::BoardFinder(const std::list<BoardConfig const *> &boardConfigs) : _boardConfigs(boardConfigs) {
}

BoardConfig const *BoardFinder::searchBoardConfig(logging::Logger &logger) {
  logger.log(logging::LoggerLevel::LOGGER_LEVEL_INFO, MODULE_NAME, "looking for a board config.");
  logger.log(logging::LoggerLevel::LOGGER_LEVEL_INFO, MODULE_NAME, "searching for OLED...");

  for (BoardConfig const *boardconf : _boardConfigs) {
    if (boardconf->needCheckPowerChip && checkPowerConfig(boardconf, logger) == boardconf->powerCheckStatus) {
      PowerManagement powerManagement;
      Wire.begin(boardconf->OledSda, boardconf->OledScl);
      powerManagement.begin(Wire);
      powerManagement.activateOLED();
      Wire.end();
    } else if (boardconf->needCheckPowerChip) {
      continue;
    }
    if (checkOledConfig(boardconf, logger)) {
      logger.log(logging::LoggerLevel::LOGGER_LEVEL_INFO, MODULE_NAME, "found a board config: %s", boardconf->Name.c_str());
      return boardconf;
    }
  }

  logger.log(logging::LoggerLevel::LOGGER_LEVEL_INFO, MODULE_NAME, "could not find OLED, will search for the modem now...");

  for (BoardConfig const *boardconf : _boardConfigs) {
    if (boardconf->needCheckPowerChip && checkPowerConfig(boardconf, logger) == boardconf->powerCheckStatus) {
      PowerManagement powerManagement;
      Wire.begin(boardconf->OledSda, boardconf->OledScl);
      powerManagement.begin(Wire);
      powerManagement.activateLoRa();
      Wire.end();
    }
    if (checkModemConfig(boardconf)) {
      logger.log(logging::LoggerLevel::LOGGER_LEVEL_INFO, MODULE_NAME, "found a board config: %s", boardconf->Name.c_str());
      return boardconf;
    }
  }

  logger.log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, MODULE_NAME, "could not find a board config!");

  return 0;
}

BoardConfig const *BoardFinder::getBoardConfig(String name) {
  std::_List_const_iterator<BoardConfig const *> elem = std::find_if(_boardConfigs.begin(), _boardConfigs.end(), [&](BoardConfig const *conf) {
    return conf->Name == name;
  });
  if (elem == _boardConfigs.end()) {
    return 0;
  }
  return *elem;
}

bool BoardFinder::checkOledConfig(BoardConfig const *boardConfig, logging::Logger &logger) {
  if (boardConfig->OledReset > 0) {
    pinMode(boardConfig->OledReset, OUTPUT);
    digitalWrite(boardConfig->OledReset, HIGH);
    delay(1);
    digitalWrite(boardConfig->OledReset, LOW);
    delay(10);
    digitalWrite(boardConfig->OledReset, HIGH);
  }
  if (!Wire.begin(boardConfig->OledSda, boardConfig->OledScl)) {
    logger.log(logging::LoggerLevel::LOGGER_LEVEL_WARN, MODULE_NAME, "issue with wire");
    return false;
  }
  Wire.beginTransmission(boardConfig->OledAddr);
  if (!Wire.endTransmission()) {
    Wire.end();
    return true;
  }
  Wire.end();
  return false;
}

bool BoardFinder::checkModemConfig(BoardConfig const *boardConfig) {
  pinMode(boardConfig->LoraReset, OUTPUT);
  digitalWrite(boardConfig->LoraReset, LOW);
  delay(10);
  digitalWrite(boardConfig->LoraReset, HIGH);
  delay(10);

  pinMode(boardConfig->LoraCS, OUTPUT);
  digitalWrite(boardConfig->LoraCS, HIGH);

  SPI.begin(boardConfig->LoraSck, boardConfig->LoraMiso, boardConfig->LoraMosi, boardConfig->LoraCS);

  digitalWrite(boardConfig->LoraCS, LOW);

  SPI.beginTransaction(SPISettings(8E6, MSBFIRST, SPI_MODE0));
  SPI.transfer(0x42);
  uint8_t response = SPI.transfer(0x00);
  SPI.endTransaction();
  digitalWrite(boardConfig->LoraCS, HIGH);
  SPI.end();
  if (response == 0x12) {
    return true;
  }
  return false;
}

bool BoardFinder::checkPowerConfig(BoardConfig const *boardConfig, logging::Logger &logger) {
  if (!Wire.begin(boardConfig->OledSda, boardConfig->OledScl)) {
    logger.log(logging::LoggerLevel::LOGGER_LEVEL_WARN, MODULE_NAME, "issue with wire");
    return false;
  }
  Wire.beginTransmission(0x34);
  Wire.write(0x03);
  Wire.endTransmission();

  Wire.requestFrom(0x34, 1);
  int response = Wire.read();
  Wire.endTransmission();
  Wire.end();

  logger.log(logging::LoggerLevel::LOGGER_LEVEL_DEBUG, MODULE_NAME, "wire response: %d", response);
  if (response == 0x03) {
    logger.log(logging::LoggerLevel::LOGGER_LEVEL_DEBUG, MODULE_NAME, "power chip found!");
    return true;
  }
  logger.log(logging::LoggerLevel::LOGGER_LEVEL_DEBUG, MODULE_NAME, "power chip NOT found");
  return false;
}

// clang-format off
BoardConfig TTGO_LORA32_V1        ("TTGO_LORA32_V1",         eTTGO_LORA32_V1,          4, 15, 0x3C,  0,  5, 19, 27, 18, 14, 26,  0,  0,  0);
BoardConfig TTGO_LORA32_V2        ("TTGO_LORA32_V2",         eTTGO_LORA32_V2,         21, 22, 0x3C,  0,  5, 19, 27, 18, 14, 26,  0,  0,  0);
BoardConfig TTGO_T_Beam_V0_7      ("TTGO_T_Beam_V0_7",       eTTGO_T_Beam_V0_7,       21, 22, 0x3C,  0,  5, 19, 27, 18, 14, 26, 15, 12, 38, true);
BoardConfig TTGO_T_Beam_V1_0      ("TTGO_T_Beam_V1_0",       eTTGO_T_Beam_V1_0,       21, 22, 0x3C,  0,  5, 19, 27, 18, 14, 26, 12, 34, 38, true, true);
BoardConfig ETH_BOARD             ("ETH_BOARD",              eETH_BOARD,              33, 32, 0x3C,  0, 14,  2, 15, 12,  4, 36,  0,  0,  0);
BoardConfig TRACKERD              ("TRACKERD",               eTRACKERD,                5,  4, 0x3C,  0, 18, 19, 23, 16, 14, 26,  0,  0,  0);
BoardConfig HELTEC_WIFI_LORA_32_V1("HELTEC_WIFI_LORA_32_V1", eHELTEC_WIFI_LORA_32_V1,  4, 15, 0x3C, 16,  5, 19, 27, 18, 14, 26,  0,  0,  0);
BoardConfig HELTEC_WIFI_LORA_32_V2("HELTEC_WIFI_LORA_32_V2", eHELTEC_WIFI_LORA_32_V2,  4, 15, 0x3C, 16,  5, 19, 27, 18, 14, 26,  0,  0,  0);
BoardConfig GUALTHERIUS_LORAHAM_v100("GUALTHERIUS_LORAHAM_v100", eGUALTHERIUS_LORAHAM_v100, 17, 16, 0x3C,  0, 18, 19, 23,  5, 13, 35, 0, 0, 0);
BoardConfig GUALTHERIUS_LORAHAM_v106("GUALTHERIUS_LORAHAM_v106", eGUALTHERIUS_LORAHAM_v106, 17, 16, 0x3C,  0, 18, 19, 23,  2, 13, 35, 0, 0, 0);
// clang-format on
