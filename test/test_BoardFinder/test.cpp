#include <Arduino.h>
#include <unity.h>

#include <BoardFinder.h>

std::list<BoardConfig const *> boardConfigs;
logging::Logger                logger;
BoardFinder                   *finder = 0;

void setUp(void) {
  boardConfigs.push_back(&TTGO_LORA32_V1);
  boardConfigs.push_back(&TTGO_LORA32_V2);
  boardConfigs.push_back(&TTGO_T_Beam_V1_0);
  boardConfigs.push_back(&LILYGO_POE_ETH_BOARD);
  boardConfigs.push_back(&HELTEC_WIFI_LORA_32_V1);
  boardConfigs.push_back(&HELTEC_WIFI_LORA_32_V2);

  finder = new BoardFinder(boardConfigs);

  logger.setSerial(&Serial);
}

void tearDown(void) {
  delete finder;
  finder = 0;
}

void test_oled_found(void) {
  bool found = false;
  for (auto boardConfig : boardConfigs) {
    if (finder->checkOledConfig(boardConfig, logger)) {
      TEST_PRINTF("found: %s", boardConfig->Name.c_str());
      found = true;
      break;
    }
  }
  TEST_ASSERT_TRUE(found);
}

void test_modem_found(void) {
  bool found = false;
  for (auto boardConfig : boardConfigs) {
    if (finder->checkModemConfig(boardConfig)) {
      TEST_PRINTF("found: %s", boardConfig->Name.c_str());
      found = true;
      break;
    }
  }
  TEST_ASSERT_TRUE(found);
}

void test_search_board_config(void) {
  BoardConfig const *boardConfig = finder->searchBoardConfig(logger);
  TEST_ASSERT_NOT_NULL(boardConfig);
}

void test_get_board_config(void) {
  BoardConfig const *boardConfig = finder->getBoardConfig("LILYGO_POE_ETH_BOARD");
  TEST_ASSERT_NOT_NULL(boardConfig);
}

void test_get_board_config_negative(void) {
  BoardConfig const *boardConfig = finder->getBoardConfig("NO BOARD");
  TEST_ASSERT_NULL(boardConfig);
}

void setup() {
  UNITY_BEGIN();
  RUN_TEST(test_oled_found);
  RUN_TEST(test_modem_found);
  RUN_TEST(test_search_board_config);
  RUN_TEST(test_get_board_config);
  RUN_TEST(test_get_board_config_negative);
  UNITY_END();
}

void loop() {
}
