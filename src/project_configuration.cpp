#include <SPIFFS.h>

#include <logger.h>

#include "project_configuration.h"

void ProjectConfigurationManagement::readProjectConfiguration(DynamicJsonDocument &data, Configuration &conf) {
  if (data.containsKey("callsign"))
    conf.callsign = data["callsign"].as<String>();

  if (data.containsKey("network") && data["network"].containsKey("DHCP")) {
    conf.network.DHCP = data["network"]["DHCP"];
    conf.network.staticIP.fromString(data["network"]["staticIP"].as<String>());
    conf.network.subnet.fromString(data["network"]["subnet"].as<String>());
    conf.network.gateway.fromString(data["network"]["gateway"].as<String>());
    conf.network.dns1.fromString(data["network"]["dns1"].as<String>());
    conf.network.dns2.fromString(data["network"]["dns2"].as<String>());
  }

  JsonArray aps = data["wifi"]["AP"].as<JsonArray>();
  for (JsonVariant v : aps) {
    Configuration::Wifi::AP ap;
    ap.SSID     = v["SSID"].as<String>();
    ap.password = v["password"].as<String>();
    conf.wifi.APs.push_back(ap);
  }
  if (data.containsKey("beacon") && data["beacon"].containsKey("message"))
    conf.beacon.message = data["beacon"]["message"].as<String>();
  conf.beacon.positionLatitude  = data["beacon"]["position"]["latitude"] | 0.0;
  conf.beacon.positionLongitude = data["beacon"]["position"]["longitude"] | 0.0;
  conf.beacon.timeout           = data["beacon"]["timeout"] | 15;
  conf.aprs_is.active           = data["aprs_is"]["active"] | true;
  if (data.containsKey("aprs_is") && data["aprs_is"].containsKey("passcode"))
    conf.aprs_is.passcode = data["aprs_is"]["passcode"].as<String>();
  if (data.containsKey("aprs_is") && data["aprs_is"].containsKey("server"))
    conf.aprs_is.server = data["aprs_is"]["server"].as<String>();
  conf.aprs_is.port = data["aprs_is"]["port"] | 14580;

  conf.digi.active            = data["digi"]["active"] | false;
  conf.digi.beacon            = data["digi"]["beacon"] | false;

  conf.lora.rxFrequency       = data["lora"]["rxFrequency"] | 433775000;
  conf.lora.rxSpreadingFactor = data["lora"]["rxSpreadingFactor"] | 12;
  conf.lora.rxSignalBandwidth = data["lora"]["rxSignalBandwidth"] | 125000;
  conf.lora.rxCodingRate4     = data["lora"]["rxCodingRate4"] | 5;
  conf.lora.rxGain            = data["lora"]["rxGain"]        | 1;

  conf.lora.txFrequency       = data["lora"]["txFrequency"] | 433775000;
  conf.lora.txSpreadingFactor = data["lora"]["txSpreadingFactor"] | 12;
  conf.lora.txSignalBandwidth = data["lora"]["txSignalBandwidth"] | 125000;
  conf.lora.txCodingRate4     = data["lora"]["txCodingRate4"] | 5;
  conf.lora.txPower           = data["lora"]["txPower"] | 20;

  conf.display.alwaysOn       = data["display"]["always_on"] | true;
  conf.display.timeout        = data["display"]["timeout"] | 10;
  conf.display.overwritePin   = data["display"]["overwrite_pin"] | 0;
  conf.display.turn180        = data["display"]["turn180"] | true;

  conf.ftp.active = data["ftp"]["active"] | false;
  JsonArray users = data["ftp"]["user"].as<JsonArray>();
  for (JsonVariant u : users) {
    Configuration::Ftp::User us;
    us.name     = u["name"].as<String>();
    us.password = u["password"].as<String>();
    conf.ftp.users.push_back(us);
  }
  if (conf.ftp.users.empty()) {
    Configuration::Ftp::User us;
    us.name     = "ftp";
    us.password = "ftp";
    conf.ftp.users.push_back(us);
  }
  if (data.containsKey("ntp_server"))
    conf.ntpServer = data["ntp_server"].as<String>();

  if (data.containsKey("board"))
    conf.board = data["board"].as<String>();
}

void ProjectConfigurationManagement::writeProjectConfiguration(Configuration &conf, DynamicJsonDocument &data) {
  data["callsign"] = conf.callsign;

  if (!conf.network.DHCP) {
    data["network"]["DHCP"]     = conf.network.DHCP;
    data["network"]["staticIP"] = conf.network.staticIP.toString();
    data["network"]["subnet"]   = conf.network.subnet.toString();
    data["network"]["gateway"]  = conf.network.gateway.toString();
    data["network"]["dns1"]     = conf.network.dns1.toString();
    data["network"]["dns2"]     = conf.network.dns2.toString();
  }

  JsonArray aps = data["wifi"].createNestedArray("AP");
  for (Configuration::Wifi::AP ap : conf.wifi.APs) {
    JsonObject v  = aps.createNestedObject();
    v["SSID"]     = ap.SSID;
    v["password"] = ap.password;
  }
  data["beacon"]["message"]               = conf.beacon.message;
  data["beacon"]["position"]["latitude"]  = conf.beacon.positionLatitude;
  data["beacon"]["position"]["longitude"] = conf.beacon.positionLongitude;
  data["beacon"]["timeout"]               = conf.beacon.timeout;
  data["aprs_is"]["active"]               = conf.aprs_is.active;
  data["aprs_is"]["passcode"]             = conf.aprs_is.passcode;
  data["aprs_is"]["server"]               = conf.aprs_is.server;
  data["aprs_is"]["port"]                 = conf.aprs_is.port;
  data["digi"]["active"]                  = conf.digi.active;
  data["digi"]["beacon"]                  = conf.digi.beacon;
  data["lora"]["rxFrequency"]             = conf.lora.rxFrequency;
  data["lora"]["rxSpreadingFactor"]       = conf.lora.rxSpreadingFactor;
  data["lora"]["rxSignalBandwidth"]       = conf.lora.rxSignalBandwidth;
  data["lora"]["rxCodingRate4"]           = conf.lora.rxCodingRate4;
  data["lora"]["rxGain"]                  = conf.lora.rxGain;
  data["lora"]["txFrequency"]             = conf.lora.txFrequency;
  data["lora"]["txSpreadingFactor"]       = conf.lora.txSpreadingFactor;
  data["lora"]["txSignalBandwidth"]       = conf.lora.txSignalBandwidth;
  data["lora"]["txCodingRate4"]           = conf.lora.txCodingRate4;
  data["lora"]["txPower"]                 = conf.lora.txPower;
  data["display"]["always_on"]            = conf.display.alwaysOn;
  data["display"]["timeout"]              = conf.display.timeout;
  data["display"]["overwrite_pin"]        = conf.display.overwritePin;
  data["display"]["turn180"]              = conf.display.turn180;
  data["ftp"]["active"]                   = conf.ftp.active;
  JsonArray users                         = data["ftp"].createNestedArray("user");
  for (Configuration::Ftp::User u : conf.ftp.users) {
    JsonObject v  = users.createNestedObject();
    v["name"]     = u.name;
    v["password"] = u.password;
  }
  data["ntp_server"] = conf.ntpServer;

  data["board"] = conf.board;
}
