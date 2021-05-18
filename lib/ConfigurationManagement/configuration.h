#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <list>
#include <memory>

#include <Arduino.h>
#ifndef CPPCHECK
#include <ArduinoJson.h>
#endif

class Configuration;

class ConfigurationManagement {
public:
  explicit ConfigurationManagement(String FilePath);
  virtual ~ConfigurationManagement();

  void readConfiguration(Configuration &conf);
  void writeConfiguration(Configuration &conf);

private:
  virtual void readProjectConfiguration(DynamicJsonDocument &data, Configuration &conf)  = 0;
  virtual void writeProjectConfiguration(Configuration &conf, DynamicJsonDocument &data) = 0;

  const String mFilePath;
};

#endif
