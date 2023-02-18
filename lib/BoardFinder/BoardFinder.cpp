#include "BoardFinder.h"
#include <logger.h>
#include <power_management.h>

#define MODULE_NAME "BoardFinder"

OledPins::OledPins(int8_t sda, int8_t scl, int8_t reset, int8_t addr) : Sda(sda), Scl(scl), Reset(reset), Addr(addr) {
}

LoraPins::LoraPins(int8_t sck, int8_t miso, int8_t mosi, int8_t cs, int8_t reset, int8_t irq) : Sck(sck), Miso(miso), Mosi(mosi), CS(cs), Reset(reset), IRQ(irq) {
}

GpsPins::GpsPins(int8_t rx, int8_t tx) : Rx(rx), Tx(tx) {
}

EthernetPins::EthernetPins(int8_t mdc, int8_t mdio, int8_t nreset, int8_t addr, int8_t power, eth_clock_mode_t clk, eth_phy_type_t type) : MDC(mdc), MDIO(mdio), nReset(nreset), Addr(addr), Power(power), CLK(clk), Type(type) {
}

ButtonPins::ButtonPins(int8_t pin) : Pin(pin) {
}

BoardConfig::BoardConfig(String name, BoardType type, OledPins oled, LoraPins lora, GpsPins gps, EthernetPins ethernet, ButtonPins button, bool needcheckpowerchip, bool powercheckstatus) : Name(name), Type(type), Oled(oled), Lora(lora), Gps(gps), Ethernet(ethernet), Button(button), needCheckPowerChip(needcheckpowerchip), powerCheckStatus(powercheckstatus) {
}

BoardFinder::BoardFinder(const std::list<BoardConfig const *> &boardConfigs) : _boardConfigs(boardConfigs) {
}

BoardConfig const *BoardFinder::searchBoardConfig(logging::Logger &logger) {
  logger.log(logging::LoggerLevel::LOGGER_LEVEL_INFO, MODULE_NAME, "looking for a board config.");
  logger.log(logging::LoggerLevel::LOGGER_LEVEL_INFO, MODULE_NAME, "searching for OLED...");

  for (BoardConfig const *boardconf : _boardConfigs) {
    if (boardconf->needCheckPowerChip && checkPowerConfig(boardconf, logger) == boardconf->powerCheckStatus) {
      PowerManagement powerManagement;
      Wire.begin(boardconf->Oled.Sda, boardconf->Oled.Scl);
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
      Wire.begin(boardconf->Oled.Sda, boardconf->Oled.Scl);
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
  if (boardConfig->Oled.Reset != -1) {
    pinMode(boardConfig->Oled.Reset, OUTPUT);
    digitalWrite(boardConfig->Oled.Reset, HIGH);
    delay(1);
    digitalWrite(boardConfig->Oled.Reset, LOW);
    delay(10);
    digitalWrite(boardConfig->Oled.Reset, HIGH);
  }
  if (!Wire.begin(boardConfig->Oled.Sda, boardConfig->Oled.Scl)) {
    logger.log(logging::LoggerLevel::LOGGER_LEVEL_WARN, MODULE_NAME, "issue with wire");
    return false;
  }
  Wire.beginTransmission(boardConfig->Oled.Addr);
  if (!Wire.endTransmission()) {
    Wire.end();
    return true;
  }
  Wire.end();
  return false;
}

bool BoardFinder::checkModemConfig(BoardConfig const *boardConfig) {
  pinMode(boardConfig->Lora.Reset, OUTPUT);
  digitalWrite(boardConfig->Lora.Reset, LOW);
  delay(10);
  digitalWrite(boardConfig->Lora.Reset, HIGH);
  delay(10);

  pinMode(boardConfig->Lora.CS, OUTPUT);
  digitalWrite(boardConfig->Lora.CS, HIGH);

  SPI.begin(boardConfig->Lora.Sck, boardConfig->Lora.Miso, boardConfig->Lora.Mosi, boardConfig->Lora.CS);

  digitalWrite(boardConfig->Lora.CS, LOW);

  SPI.beginTransaction(SPISettings(8E6, MSBFIRST, SPI_MODE0));
  SPI.transfer(0x42);
  uint8_t response = SPI.transfer(0x00);
  SPI.endTransaction();
  digitalWrite(boardConfig->Lora.CS, HIGH);
  SPI.end();
  if (response == 0x12) {
    return true;
  }
  return false;
}

bool BoardFinder::checkPowerConfig(BoardConfig const *boardConfig, logging::Logger &logger) {
  if (!Wire.begin(boardConfig->Oled.Sda, boardConfig->Oled.Scl)) {
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
BoardConfig TTGO_LORA32_V1          ("TTGO_LORA32_V1",           eTTGO_LORA32_V1,           OledPins( 4, 15),     LoraPins( 5, 19, 27, 18, 14, 26));
BoardConfig TTGO_LORA32_V2          ("TTGO_LORA32_V2",           eTTGO_LORA32_V2,           OledPins(21, 22),     LoraPins( 5, 19, 27, 18, 14, 26));
BoardConfig TTGO_T_Beam_V0_7        ("TTGO_T_Beam_V0_7",         eTTGO_T_Beam_V0_7,         OledPins(21, 22),     LoraPins( 5, 19, 27, 18, 14, 26), GpsPins(15, 12), EthernetPins(),           ButtonPins(38), true);
BoardConfig TTGO_T_Beam_V1_0        ("TTGO_T_Beam_V1_0",         eTTGO_T_Beam_V1_0,         OledPins(21, 22),     LoraPins( 5, 19, 27, 18, 14, 26), GpsPins(12, 34), EthernetPins(),           ButtonPins(38), true, true);
BoardConfig LILYGO_POE_ETH_BOARD    ("LILYGO_POE_ETH_BOARD",     eLILYGO_POE_ETH_BOARD,     OledPins(33, 32),     LoraPins(14,  2, 15, 12,  4, 36), GpsPins(),       EthernetPins(23, 18,  5, 0, -1, ETH_CLOCK_GPIO17_OUT, ETH_PHY_LAN8720));
BoardConfig WT32_ETH_BOARD          ("WT32_ETH_BOARD",           eWT32_ETH_BOARD,           OledPins(17,  5),     LoraPins(14,  2, 15, 12,  4, 36), GpsPins(),       EthernetPins(23, 18, -1, 1, 16, ETH_CLOCK_GPIO0_IN,   ETH_PHY_LAN8720));
BoardConfig TRACKERD                ("TRACKERD",                 eTRACKERD,                 OledPins( 5,  4),     LoraPins(18, 19, 23, 16, 14, 26));
BoardConfig HELTEC_WIFI_LORA_32_V1  ("HELTEC_WIFI_LORA_32_V1",   eHELTEC_WIFI_LORA_32_V1,   OledPins( 4, 15, 16), LoraPins( 5, 19, 27, 18, 14, 26));
BoardConfig HELTEC_WIFI_LORA_32_V2  ("HELTEC_WIFI_LORA_32_V2",   eHELTEC_WIFI_LORA_32_V2,   OledPins( 4, 15, 16), LoraPins( 5, 19, 27, 18, 14, 26));
BoardConfig GUALTHERIUS_LORAHAM_v100("GUALTHERIUS_LORAHAM_v100", eGUALTHERIUS_LORAHAM_v100, OledPins(17, 16),     LoraPins(18, 19, 23,  5, 13, 35));
BoardConfig GUALTHERIUS_LORAHAM_v106("GUALTHERIUS_LORAHAM_v106", eGUALTHERIUS_LORAHAM_v106, OledPins(17, 16),     LoraPins(18, 19, 23,  2, 13, 35));
// clang-format on
