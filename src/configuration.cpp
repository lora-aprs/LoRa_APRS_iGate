#include "SPIFFS.h"

#include "configuration.h"
#include "settings.h"


Configuration::Configuration(String FilePath)
	: mFilePath(FilePath), mData(1024)
{
	if(!SPIFFS.begin(true))
	{
		Serial.println("[ERROR] Mounting SPIFFS was not possible. Trying to format SPIFFS...");
		SPIFFS.format();
		if(!SPIFFS.begin())
		{
			Serial.println("[ERROR] Formating SPIFFS was not okay!");
			return;
		}
	}
	if(SPIFFS.exists(mFilePath))
	{
		readFile();
	}
	else
	{
		mData["Wifi"]["Name"] = WIFI_NAME;
		mData["Wifi"]["Password"] = WIFI_KEY;
		mData["IS"]["Call"] = USER;
		mData["IS"]["Password"] = PASS;
		mData["IS"]["Server"] = SERVER;
		mData["IS"]["Port"] = PORT;
		mData["Beacon"]["Message"] = BEACON_MESSAGE;
		mData["Beacon"]["Pos"]["Lat"] = BEACON_LAT_POS;
		mData["Beacon"]["Pos"]["Long"] = BEACON_LONG_POS;
		mData["Beacon"]["Timeout"] = BEACON_TIMEOUT;
		writeFile();
	}
}

String Configuration::getWifiName() const
{
	return mData["Wifi"]["Name"];
}

void Configuration::setWifiName(String WifiName)
{
	mData["Wifi"]["Name"] = WifiName;
}

String Configuration::getWifiPassword() const
{
	return mData["Wifi"]["Password"];
}

void Configuration::setWifiPassword(String WifiPassword)
{
	mData["Wifi"]["Password"] = WifiPassword;
}

String Configuration::getIsCall() const
{
	return mData["IS"]["Call"];
}

void Configuration::setIsCall(String IsCall)
{
	mData["IS"]["Call"] = IsCall;
}

String Configuration::getIsPassword() const
{
	return mData["IS"]["Password"];
}

void Configuration::setIsPassword(String IsPassword)
{
	mData["IS"]["Password"] = IsPassword;
}

String Configuration::getIsServer() const
{
	return mData["IS"]["Server"];
}

void Configuration::setIsServer(String IsServer)
{
	mData["IS"]["Server"] = IsServer;
}

int Configuration::getIsPort() const
{
	return mData["IS"]["Port"];
}

void Configuration::setIsPort(int IsPort)
{
	mData["IS"]["Port"] = IsPort;
}

String Configuration::getBeaconMessage() const
{
	return mData["Beacon"]["Message"];
}

void Configuration::setBeaconMessage(String BeaconMessage)
{
	mData["Beacon"]["Message"] = BeaconMessage;
}

String Configuration::getBeaconPosLat() const
{
	return mData["Beacon"]["Pos"]["Lat"];
}

void Configuration::setBeaconPosLat(String BeaconPosLat)
{
	mData["Beacon"]["Pos"]["Lat"] = BeaconPosLat;
}

String Configuration::getBeaconPosLong() const
{
	return mData["Beacon"]["Pos"]["Long"];
}

void Configuration::setBeaconPosLong(String BeaconPosLong)
{
	mData["Beacon"]["Pos"]["Long"] = BeaconPosLong;
}

int Configuration::getBeaconTimeout() const
{
	return mData["Beacon"]["Timeout"];
}

void Configuration::setBeaconTimeout(int BeaconTimeout)
{
	mData["Beacon"]["Timeout"] = BeaconTimeout;
}


void Configuration::readFile()
{
	File file = SPIFFS.open(mFilePath);
	if(!file)
	{
		Serial.println("Failed to open file for reading...");
		return;
	}
	deserializeJson(mData, file);
	file.close();
}

void Configuration::writeFile()
{
	File file = SPIFFS.open(mFilePath, "w");
	if(!file)
	{
		Serial.println("Failed to open file for writing...");
		return;
	}
	serializeJson(mData, file);
	serializeJson(mData, Serial);
	Serial.println();
	file.close();
}
