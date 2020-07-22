#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <Arduino.h>
#include <ArduinoJson.h>

class Configuration
{
public:
	Configuration(String FilePath);

	void readFile();
	void writeFile();

	String getWifiName() const;
	void   setWifiName(String WifiName);
	String getWifiPassword() const;
	void   setWifiPassword(String WifiPassword);

	String getIsCall() const;
	void   setIsCall(String IsCall);
	String getIsPassword() const;
	void   setIsPassword(String IsPassword);
	String getIsServer() const;
	void   setIsServer(String IsServer);
	int    getIsPort() const;
	void   setIsPort(int IsPort);

	String getBeaconMessage() const;
	void   setBeaconMessage(String BeaconMessage);
	String getBeaconPosLat() const;
	void   setBeaconPosLat(String BeaconPosLat);
	String getBeaconPosLong() const;
	void   setBeaconPosLong(String BeaconPosLong);
	int    getBeaconTimeout() const;
	void   setBeaconTimeout(int BeaconTimeout);


private:
	const String mFilePath;

	DynamicJsonDocument mData;
};

#endif
