#include "configuration.h"
#include <SPIFFS.h>
#include <logger.h>

#define MODULE_NAME "ConfigurationManagement"

ConfigurationManagement::ConfigurationManagement(logging::Logger &logger, String FilePath) : mFilePath(FilePath) {
  if (!SPIFFS.begin(true)) {
    logger.log(logging::LoggerLevel::LOGGER_LEVEL_INFO, MODULE_NAME, "Mounting SPIFFS was not possible. Trying to format SPIFFS...");
    SPIFFS.format();
    if (!SPIFFS.begin()) {
      logger.log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, MODULE_NAME, "Formatting SPIFFS was not okay!");
    }
  }
}

ConfigurationManagement::~ConfigurationManagement() {
}

void ConfigurationManagement::readConfiguration(logging::Logger &logger, Configuration &conf) {
  File file = SPIFFS.open(mFilePath);
  if (!file) {
    logger.log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, MODULE_NAME, "Failed to open file for reading, using default configuration.");
    return;
  }
  JsonDocument  data;
  DeserializationError error = deserializeJson(data, file);
  if (error) {
    logger.log(logging::LoggerLevel::LOGGER_LEVEL_WARN, MODULE_NAME, "Failed to read file, using default configuration.");
  }
  // serializeJson(data, Serial);
  // Serial.println();
  file.close();

  readProjectConfiguration(data, conf);

  // update config in memory to get the new fields:
  // writeConfiguration(logger, conf);
}

void ConfigurationManagement::writeConfiguration(logging::Logger &logger, Configuration &conf) {
  File file = SPIFFS.open(mFilePath, "w");
  if (!file) {
    logger.log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, MODULE_NAME, "Failed to open file for writing...");
    return;
  }
  JsonDocument data;

  writeProjectConfiguration(conf, data);

  serializeJson(data, file);
  // serializeJson(data, Serial);
  // Serial.println();
  file.close();
}
