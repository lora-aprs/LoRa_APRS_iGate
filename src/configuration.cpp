#include "SPIFFS.h"

#include "configuration.h"


ConfigurationManagement::ConfigurationManagement(String FilePath)
	: mFilePath(FilePath)
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
	if(!SPIFFS.exists(mFilePath))
	{
		Configuration conf;
		writeConfiguration(conf);
	}
}

Configuration ConfigurationManagement::readConfiguration()
{
	File file = SPIFFS.open(mFilePath);
	if(!file)
	{
		Serial.println("Failed to open file for reading...");
		return Configuration();
	}
	DynamicJsonDocument data(2048);
	deserializeJson(data, file);
	//serializeJson(data, Serial);
	//Serial.println();
	file.close();

	Configuration conf;
	conf.callsign                 = data["callsign"].as<String>();
	conf.wifi.active              = data["wifi"]["active"];
	JsonArray aps                 = data["wifi"]["AP"].as<JsonArray>();
	for(JsonVariant v : aps)
	{
		Configuration::Wifi::AP ap;
		ap.SSID                   = v["SSID"].as<String>();
		ap.password               = v["password"].as<String>();
		conf.wifi.APs.push_back(ap);
	}
	conf.beacon.message           = data["beacon"]["message"].as<String>();
	conf.beacon.positionLatitude  = data["beacon"]["position"]["latitude"];
	conf.beacon.positionLongitude = data["beacon"]["position"]["longitude"];
	conf.aprs_is.active           = data["aprs_is"]["active"];
	conf.aprs_is.password         = data["aprs_is"]["password"].as<String>();
	conf.aprs_is.server           = data["aprs_is"]["server"].as<String>();
	conf.aprs_is.port             = data["aprs_is"]["port"];
	conf.aprs_is.beacon           = data["aprs_is"]["beacon"];
	conf.aprs_is.beaconTimeout    = data["aprs_is"]["beacon_timeout"];
	conf.digi.active              = data["digi"]["active"];
	conf.digi.forwardTimeout      = data["digi"]["forward_timeout"];
	conf.digi.beacon              = data["digi"]["beacon"];
	conf.digi.beaconTimeout       = data["digi"]["beacon_timeout"];

	if(data["version"] >= 2)
	{
		conf.lora.frequencyRx     = data["lora"]["frequency_rx"];
		conf.lora.frequencyTx     = data["lora"]["frequency_tx"];
		conf.lora.power           = data["lora"]["power"];
		conf.display.alwaysOn     = data["display"]["always_on"];
		conf.display.timeout      = data["display"]["timeout"];
		conf.display.overwritePin = data["display"]["overwrite_pin"];
	}
	if(data["version"] >= 3)
	{
		conf.lora.spreadingFactor = data["lora"]["spreading_factor"];
		conf.lora.signalBandwidth = data["lora"]["signal_bandwidth"];
		conf.lora.codingRate4     = data["lora"]["coding_rate4"];
	}
	if(data["version"] >= 4)
	{
		conf.ftp.active           = data["ftp"]["active"];
		JsonArray users           = data["ftp"]["user"].as<JsonArray>();
		for(JsonVariant u : users)
		{
			Configuration::Ftp::User us;
			us.name               = u["name"].as<String>();
			us.password           = u["password"].as<String>();
			conf.ftp.users.push_back(us);
		}
	}

	// update config in memory to get the new fields:
	writeConfiguration(conf);

	return conf;
}

void ConfigurationManagement::writeConfiguration(Configuration conf)
{
	File file = SPIFFS.open(mFilePath, "w");
	if(!file)
	{
		Serial.println("Failed to open file for writing...");
		return;
	}
	DynamicJsonDocument data(2048);

	data["version"]                         = conf.version;
	data["callsign"]                        = conf.callsign;
	data["wifi"]["active"]                  = conf.wifi.active;
	JsonArray aps = data["wifi"].createNestedArray("AP");
	for(Configuration::Wifi::AP ap : conf.wifi.APs)
	{
		JsonObject v = aps.createNestedObject();
		v["SSID"] = ap.SSID;
		v["password"] = ap.password;
	}
	data["beacon"]["message"]               = conf.beacon.message;
	data["beacon"]["position"]["latitude"]  = conf.beacon.positionLatitude;
	data["beacon"]["position"]["longitude"] = conf.beacon.positionLongitude;
	data["aprs_is"]["active"]               = conf.aprs_is.active;
	data["aprs_is"]["password"]             = conf.aprs_is.password;
	data["aprs_is"]["server"]               = conf.aprs_is.server;
	data["aprs_is"]["port"]                 = conf.aprs_is.port;
	data["aprs_is"]["beacon"]               = conf.aprs_is.beacon;
	data["aprs_is"]["beacon_timeout"]       = conf.aprs_is.beaconTimeout;
	data["digi"]["active"]                  = conf.digi.active;
	data["digi"]["forward_timeout"]         = conf.digi.forwardTimeout;
	data["digi"]["beacon"]                  = conf.digi.beacon;
	data["digi"]["beacon_timeout"]          = conf.digi.beaconTimeout;
	data["lora"]["frequency_rx"]            = conf.lora.frequencyRx;
	data["lora"]["frequency_tx"]            = conf.lora.frequencyTx;
	data["lora"]["power"]                   = conf.lora.power;
	data["lora"]["spreading_factor"]        = conf.lora.spreadingFactor;
	data["lora"]["signal_bandwidth"]        = conf.lora.signalBandwidth;
	data["lora"]["coding_rate4"]            = conf.lora.codingRate4;
	data["display"]["always_on"]            = conf.display.alwaysOn;
	data["display"]["timeout"]              = conf.display.timeout;
	data["display"]["overwrite_pin"]        = conf.display.overwritePin;
	data["ftp"]["active"]                   = conf.ftp.active;
	JsonArray users = data["ftp"].createNestedArray("user");
	for(Configuration::Ftp::User u : conf.ftp.users)
	{
		JsonObject v = users.createNestedObject();
		v["name"] = u.name;
		v["password"] = u.password;
	}

	serializeJson(data, file);
	//serializeJson(data, Serial);
	//Serial.println();
	file.close();
}
