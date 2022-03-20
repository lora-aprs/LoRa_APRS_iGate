#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <list>
#include <memory>

#include <Arduino.h>
#ifndef CPPCHECK
#include <ArduinoJson.h>
#endif

#include <logger.h>

class Configuration;

class ConfigurationManagement {
public:
  explicit ConfigurationManagement(logging::Logger &logger, String FilePath);
  virtual ~ConfigurationManagement();

  void readConfiguration(logging::Logger &logger, Configuration &conf);
  void writeConfiguration(logging::Logger &logger, Configuration &conf);

private:
  virtual void readProjectConfiguration(DynamicJsonDocument &data, Configuration &conf)  = 0;
  virtual void writeProjectConfiguration(Configuration &conf, DynamicJsonDocument &data) = 0;

  const String mFilePath;
};

#endif
