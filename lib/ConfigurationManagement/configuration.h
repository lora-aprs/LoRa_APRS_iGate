#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <list>

#include <Arduino.h>
#include <ArduinoJson.h>

class Configuration;

class ConfigurationManagement
{
public:
	explicit ConfigurationManagement(String FilePath);
	virtual ~ConfigurationManagement();

	std::shared_ptr<Configuration> readConfiguration();
	void writeConfiguration(std::shared_ptr<Configuration> conf);

private:
	virtual std::shared_ptr<Configuration> readProjectConfiguration(DynamicJsonDocument & data) = 0;
	virtual void writeProjectConfiguration(std::shared_ptr<Configuration> conf, DynamicJsonDocument & data) = 0;

	const String mFilePath;
};

#endif
