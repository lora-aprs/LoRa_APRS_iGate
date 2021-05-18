#include "configuration.h"
#include <SPIFFS.h>
#include <logger.h>

ConfigurationManagement::ConfigurationManagement(String FilePath) : mFilePath(FilePath) {
  if (!SPIFFS.begin(true)) {
    logPrintlnI("Mounting SPIFFS was not possible. Trying to format SPIFFS...");
    SPIFFS.format();
    if (!SPIFFS.begin()) {
      logPrintlnE("Formating SPIFFS was not okay!");
    }
  }
}

ConfigurationManagement::~ConfigurationManagement() {
}

void ConfigurationManagement::readConfiguration(Configuration &conf) {
  File file = SPIFFS.open(mFilePath);
  if (!file) {
    logPrintlnE("Failed to open file for reading, using default configuration.");
    return;
  }
  DynamicJsonDocument  data(2048);
  DeserializationError error = deserializeJson(data, file);
  if (error) {
    logPrintlnW("Failed to read file, using default configuration.");
  }
  // serializeJson(data, Serial);
  // Serial.println();
  file.close();

  readProjectConfiguration(data, conf);

  // update config in memory to get the new fields:
  writeConfiguration(conf);
}

void ConfigurationManagement::writeConfiguration(Configuration &conf) {
  File file = SPIFFS.open(mFilePath, "w");
  if (!file) {
    logPrintlnE("Failed to open file for writing...");
    return;
  }
  DynamicJsonDocument data(2048);

  writeProjectConfiguration(conf, data);

  serializeJson(data, file);
  // serializeJson(data, Serial);
  // Serial.println();
  file.close();
}
