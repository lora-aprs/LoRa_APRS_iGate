#include <SPIFFS.h>

#include <logger.h>

#include "project_configuration.h"

void ProjectConfigurationManagement::readProjectConfiguration(DynamicJsonDocument &data, Configuration &conf) {
  if (data.containsKey("callsign"))
    conf.callsign = data["callsign"].as<String>();

  if (data.containsKey("network")) {
    conf.network.DHCP = data["network"]["DHCP"] | false;
    if (data["network"].containsKey("static")) {
      if (data["network"]["static"].containsKey("ip"))
        conf.network.static_.ip.fromString(data["network"]["static"]["ip"].as<String>());
      if (data["network"]["static"].containsKey("subnet"))
        conf.network.static_.subnet.fromString(data["network"]["static"]["subnet"].as<String>());
      if (data["network"]["static"].containsKey("gateway"))
        conf.network.static_.gateway.fromString(data["network"]["static"]["gateway"].as<String>());
      if (data["network"]["static"].containsKey("dns1"))
        conf.network.static_.dns1.fromString(data["network"]["static"]["dns1"].as<String>());
      if (data["network"]["static"].containsKey("dns2"))
        conf.network.static_.dns2.fromString(data["network"]["static"]["dns2"].as<String>());
    }
    if (data["network"].containsKey("hostname")) {
      conf.network.hostname.overwrite = data["network"]["hostname"]["overwrite"] | false;
      if (data["network"]["hostname"].containsKey("name"))
        conf.network.hostname.name = data["network"]["hostname"]["name"].as<String>();
    }
  }

  conf.wifi.active = data["wifi"]["active"];
  JsonArray aps    = data["wifi"]["AP"].as<JsonArray>();
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

  conf.digi.active          = data["digi"]["active"] | false;
  conf.digi.beacon          = data["digi"]["beacon"] | false;
  conf.lora.frequencyRx     = data["lora"]["frequency_rx"] | 433775000;
  conf.lora.gainRx          = data["lora"]["gain_rx"] | 0;
  conf.lora.frequencyTx     = data["lora"]["frequency_tx"] | 433775000;
  conf.lora.power           = data["lora"]["power"] | 20;
  conf.lora.spreadingFactor = data["lora"]["spreading_factor"] | 12;
  conf.lora.signalBandwidth = data["lora"]["signal_bandwidth"] | 125000;
  conf.lora.codingRate4     = data["lora"]["coding_rate4"] | 5;
  conf.lora.txok            = data["lora"]["txok"] | false;
  conf.display.alwaysOn     = data["display"]["always_on"] | true;
  conf.display.timeout      = data["display"]["timeout"] | 10;
  conf.display.overwritePin = data["display"]["overwrite_pin"] | 0;
  conf.display.turn180      = data["display"]["turn180"] | true;

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
  if (data.containsKey("mqtt")) {
    conf.mqtt.active   = data["mqtt"]["active"] | false;
    conf.mqtt.server   = data["mqtt"]["server"].as<String>();
    conf.mqtt.port     = data["mqtt"]["port"].as<uint16_t>();
    conf.mqtt.name     = data["mqtt"]["name"].as<String>();
    conf.mqtt.password = data["mqtt"]["password"].as<String>();
    conf.mqtt.topic    = data["mqtt"]["topic"].as<String>();
  }
  if (data.containsKey("ntp_server"))
    conf.ntpServer = data["ntp_server"].as<String>();

  if (data.containsKey("board"))
    conf.board = data["board"].as<String>();
}

void ProjectConfigurationManagement::writeProjectConfiguration(Configuration &conf, DynamicJsonDocument &data) {
  data["callsign"] = conf.callsign;

  if (!conf.network.DHCP) {
    data["network"]["DHCP"]                  = conf.network.DHCP;
    data["network"]["static"]["ip"]          = conf.network.static_.ip.toString();
    data["network"]["static"]["subnet"]      = conf.network.static_.subnet.toString();
    data["network"]["static"]["gateway"]     = conf.network.static_.gateway.toString();
    data["network"]["static"]["dns1"]        = conf.network.static_.dns1.toString();
    data["network"]["static"]["dns2"]        = conf.network.static_.dns2.toString();
    data["network"]["hostname"]["overwrite"] = conf.network.hostname.overwrite;
    data["network"]["hostname"]["name"]      = conf.network.hostname.name;
  }

  data["wifi"]["active"] = conf.wifi.active;
  JsonArray aps          = data["wifi"].createNestedArray("AP");
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
  data["lora"]["frequency_rx"]            = conf.lora.frequencyRx;
  data["lora"]["gain_rx"]                 = conf.lora.gainRx;
  data["lora"]["frequency_tx"]            = conf.lora.frequencyTx;
  data["lora"]["power"]                   = conf.lora.power;
  data["lora"]["spreading_factor"]        = conf.lora.spreadingFactor;
  data["lora"]["signal_bandwidth"]        = conf.lora.signalBandwidth;
  data["lora"]["coding_rate4"]            = conf.lora.codingRate4;
  data["lora"]["txok"]                    = conf.lora.txok;
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
  data["mqtt"]["active"]   = conf.mqtt.active;
  data["mqtt"]["server"]   = conf.mqtt.server;
  data["mqtt"]["port"]     = conf.mqtt.port;
  data["mqtt"]["name"]     = conf.mqtt.name;
  data["mqtt"]["password"] = conf.mqtt.password;
  data["mqtt"]["topic"]    = conf.mqtt.topic;
  data["ntp_server"]       = conf.ntpServer;

  data["board"] = conf.board;
}
