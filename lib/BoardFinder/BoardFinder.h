#ifndef BOARD_FINDER_H_
#define BOARD_FINDER_H_

#include <list>
#include <memory>

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

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

class BoardConfig
{
public:
	BoardConfig(
		String name, BoardType type,
		uint8_t oledsda, uint8_t oledscl, uint8_t oledaddr, uint8_t oledreset,
		uint8_t lorasck, uint8_t loramiso, uint8_t loramosi, uint8_t loracs, uint8_t lorareset, uint8_t lorairq,
		bool needcheckpowerchip = false, bool powercheckstatus = false);

	String Name;
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

	bool needCheckPowerChip;
	bool powerCheckStatus;
};

class BoardFinder
{
public:
	BoardFinder(std::list<std::shared_ptr<BoardConfig>> boardConfigs);

	std::shared_ptr<BoardConfig> searchBoardConfig();

	std::shared_ptr<BoardConfig> getBoardConfig(String name);

private:
	std::list<std::shared_ptr<BoardConfig>> _boardConfigs;

	bool checkOledConfig(std::shared_ptr<BoardConfig> boardConfig);
	bool checkModemConfig(std::shared_ptr<BoardConfig> boardConfig);
	bool checkPowerConfig(std::shared_ptr<BoardConfig> boardConfig);
};

#endif
