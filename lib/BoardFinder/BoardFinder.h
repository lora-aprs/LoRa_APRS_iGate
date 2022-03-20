#ifndef BOARD_FINDER_H_
#define BOARD_FINDER_H_

#include <list>
#include <memory>

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

enum BoardType
{
  eHELTEC_WIFI_LORA_32_V1,
  eHELTEC_WIFI_LORA_32_V2,
  eTTGO_LORA32_V1,
  eTTGO_LORA32_V2,
  eTTGO_T_Beam_V0_7,
  eTTGO_T_Beam_V1_0,
  eETH_BOARD,
  eTRACKERD
};

class BoardConfig {
public:
  explicit BoardConfig(String name, BoardType type, uint8_t oledsda, uint8_t oledscl, uint8_t oledaddr, uint8_t oledreset, uint8_t lorasck, uint8_t loramiso, uint8_t loramosi, uint8_t loracs, uint8_t lorareset, uint8_t lorairq, uint8_t gpsrx, uint8_t gpstx, bool needcheckpowerchip = false, bool powercheckstatus = false);

  String    Name;
  BoardType Type;

  uint8_t OledSda;
  uint8_t OledScl;
  uint8_t OledAddr;
  uint8_t OledReset;

  uint8_t LoraSck;
  uint8_t LoraMiso;
  uint8_t LoraMosi;
  uint8_t LoraCS;
  uint8_t LoraReset;
  uint8_t LoraIRQ;
  uint8_t GpsRx;
  uint8_t GpsTx;

  bool needCheckPowerChip;
  bool powerCheckStatus;
};

class BoardFinder {
public:
  explicit BoardFinder(const std::list<BoardConfig const *> &boardConfigs);

  BoardConfig const *searchBoardConfig();

  BoardConfig const *getBoardConfig(String name);

private:
  const std::list<BoardConfig const *> &_boardConfigs;

  bool checkOledConfig(BoardConfig const *boardConfig);
  bool checkModemConfig(BoardConfig const *boardConfig);
  bool checkPowerConfig(BoardConfig const *boardConfig);
};

extern BoardConfig TTGO_LORA32_V1;
extern BoardConfig TTGO_LORA32_V2;
extern BoardConfig TTGO_T_Beam_V0_7;
extern BoardConfig TTGO_T_Beam_V1_0;
extern BoardConfig ETH_BOARD;
extern BoardConfig TRACKERD;
extern BoardConfig HELTEC_WIFI_LORA_32_V1;
extern BoardConfig HELTEC_WIFI_LORA_32_V2;

#endif
