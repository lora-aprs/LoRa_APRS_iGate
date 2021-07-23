#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <ESP-Config.h>

extern ConfigPage page;

class Configuration {
public:
  class Wifi {
  public:
    Wifi();
    ConfigString ssid;
    ConfigString password;
  };

  class Beacon {
  public:
    Beacon();
    ConfigString  message;
    ConfigDecimal positionLatitude;
    ConfigDecimal positionLongitude;
    ConfigInt     timeout;
  };

  class APRS_IS {
  public:
    APRS_IS();
    ConfigBool   active;
    ConfigString passcode;
    ConfigString server;
    ConfigInt    port;
  };

  class Digi {
  public:
    Digi();
    ConfigBool active;
    ConfigBool beacon;
  };

  class LoRa {
  public:
    LoRa();
    ConfigInt frequencyRx;
    ConfigInt frequencyTx;
    ConfigInt power;
    ConfigInt spreadingFactor;
    ConfigInt signalBandwidth;
    ConfigInt codingRate4;
  };

  class Display {
  public:
    Display();
    ConfigBool alwaysOn;
    ConfigInt  timeout;
    ConfigInt  overwritePin;
    ConfigBool turn180;
  };

  class Ftp {
  public:
    Ftp();
    ConfigBool   active;
    ConfigString name;
    ConfigString password;
  };

  Configuration();
  ConfigString callsign;
  Wifi         wifi;
  Beacon       beacon;
  APRS_IS      aprs_is;
  Digi         digi;
  LoRa         lora;
  Display      display;
  Ftp          ftp;
  ConfigString board;
  ConfigString ntpServer;
};

#endif
