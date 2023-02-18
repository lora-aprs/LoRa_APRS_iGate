#ifndef BOARD_FINDER_H_
#define BOARD_FINDER_H_

#include <list>
#include <memory>

#include <Arduino.h>
#include <ETH.h>
#include <SPI.h>
#include <Wire.h>

#include <logger.h>

class OledPins {
public:
  explicit OledPins(int8_t sda, int8_t scl, int8_t reset = -1, int8_t addr = 0x3C);

  int8_t Sda;
  int8_t Scl;
  int8_t Reset;
  int8_t Addr;
};

class LoraPins {
public:
  explicit LoraPins(int8_t sck, int8_t miso, int8_t mosi, int8_t cs, int8_t reset, int8_t irq);

  int8_t Sck;
  int8_t Miso;
  int8_t Mosi;
  int8_t CS;
  int8_t Reset;
  int8_t IRQ;
};

class GpsPins {
public:
  explicit GpsPins(int8_t rx = -1, int8_t tx = -1);

  int8_t Rx;
  int8_t Tx;
};

class EthernetPins {
public:
  explicit EthernetPins(int8_t mdc = -1, int8_t mdio = -1, int8_t nreset = -1, int8_t addr = 0, int8_t power = -1, eth_clock_mode_t clk = ETH_CLOCK_GPIO17_OUT, eth_phy_type_t type = ETH_PHY_LAN8720);

  int8_t MDC;
  int8_t MDIO;
  int8_t nReset;
  int8_t Addr;
  int8_t Power;

  eth_clock_mode_t CLK;
  eth_phy_type_t   Type;

  bool isEthernetBoard() const {
    return MDC != -1;
  }
};

class ButtonPins {
public:
  explicit ButtonPins(int8_t pin = -1);

  int8_t Pin;
};

enum BoardType {
  eHELTEC_WIFI_LORA_32_V1,
  eHELTEC_WIFI_LORA_32_V2,
  eTTGO_LORA32_V1,
  eTTGO_LORA32_V2,
  eTTGO_T_Beam_V0_7,
  eTTGO_T_Beam_V1_0,
  eLILYGO_POE_ETH_BOARD,
  eWT32_ETH_BOARD,
  eTRACKERD,
  eGUALTHERIUS_LORAHAM_v100,
  eGUALTHERIUS_LORAHAM_v106
};

class BoardConfig {
public:
  explicit BoardConfig(String name, BoardType type, OledPins oled, LoraPins lora, GpsPins gps = GpsPins(), EthernetPins ethernet = EthernetPins(), ButtonPins button = ButtonPins(), bool needcheckpowerchip = false, bool powercheckstatus = false);

  String    Name;
  BoardType Type;

  OledPins     Oled;
  LoraPins     Lora;
  GpsPins      Gps;
  EthernetPins Ethernet;

  ButtonPins Button;

  bool needCheckPowerChip;
  bool powerCheckStatus;
};

class BoardFinder {
public:
  explicit BoardFinder(const std::list<BoardConfig const *> &boardConfigs);

  BoardConfig const *searchBoardConfig(logging::Logger &logger);

  BoardConfig const *getBoardConfig(String name);

#ifndef UNIT_TEST
private:
#endif
  const std::list<BoardConfig const *> &_boardConfigs;

  bool checkOledConfig(BoardConfig const *boardConfig, logging::Logger &logger);
  bool checkModemConfig(BoardConfig const *boardConfig);
  bool checkPowerConfig(BoardConfig const *boardConfig, logging::Logger &logger);
};

extern BoardConfig TTGO_LORA32_V1;
extern BoardConfig TTGO_LORA32_V2;
extern BoardConfig TTGO_T_Beam_V0_7;
extern BoardConfig TTGO_T_Beam_V1_0;
extern BoardConfig LILYGO_POE_ETH_BOARD;
extern BoardConfig WT32_ETH_BOARD;
extern BoardConfig TRACKERD;
extern BoardConfig HELTEC_WIFI_LORA_32_V1;
extern BoardConfig HELTEC_WIFI_LORA_32_V2;
extern BoardConfig GUALTHERIUS_LORAHAM_v100;
extern BoardConfig GUALTHERIUS_LORAHAM_v106;

#endif
