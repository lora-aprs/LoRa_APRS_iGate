#ifndef PROJECT_CONFIGURATION_H_
#define PROJECT_CONFIGURATION_H_

#include <BoardFinder.h>
#include <configuration.h>

class Configuration {
public:
  class Static {
  public:
    IPAddress ip;
    IPAddress subnet;
    IPAddress gateway;
    IPAddress dns1;
    IPAddress dns2;
  };

  class Hostname {
  public:
    bool   overwrite;
    String name;
  };

  class Network {
  public:
    Network() : DHCP(true) {
    }

    bool     DHCP;
    Static   static_;
    Hostname hostname;
  };

  class Wifi {
  public:
    Wifi() : active(true) {
    }

    bool active;
    class AP {
    public:
      String SSID;
      String password;
    };

    std::list<AP> APs;
  };

  class Beacon {
  public:
    Beacon() : message("LoRa iGATE & Digi, Info: github.com/peterus/LoRa_APRS_iGate"), positionLatitude(0.0), positionLongitude(0.0), timeout(15) {
    }

    String message;
    double positionLatitude;
    double positionLongitude;
    int    timeout;
  };

  class APRS_IS {
  public:
    APRS_IS() : active(true), server("euro.aprs2.net"), port(14580) {
    }

    bool   active;
    String passcode;
    String server;
    int    port;
  };

  class Digi {
  public:
    Digi() : active(false), beacon(true) {
    }

    bool active;
    bool beacon;
  };

  class LoRa {
  public:
    LoRa() : frequencyRx(433775000), frequencyTx(433775000), power(20), spreadingFactor(12), signalBandwidth(125000), codingRate4(5), tx_enable(true) {
    }

    long    frequencyRx;
    uint8_t gainRx;
    long    frequencyTx;
    int     power;
    int     spreadingFactor;
    long    signalBandwidth;
    int     codingRate4;
    bool    tx_enable;
  };

  class Display {
  public:
    Display() : alwaysOn(true), timeout(10), overwritePin(0), turn180(true) {
    }

    bool alwaysOn;
    int  timeout;
    int  overwritePin;
    bool turn180;
  };

  class Ftp {
  public:
    class User {
    public:
      String name;
      String password;
    };

    Ftp() : active(false) {
    }

    bool            active;
    std::list<User> users;
  };

  class MQTT {
  public:
    bool     active;
    String   server;
    uint16_t port;
    String   name;
    String   password;
    String   topic;
  };

  Configuration() : callsign("NOCALL-10"), board(""), ntpServer("pool.ntp.org"){};

  String  callsign;
  Network network;
  Wifi    wifi;
  Beacon  beacon;
  APRS_IS aprs_is;
  Digi    digi;
  LoRa    lora;
  Display display;
  Ftp     ftp;
  MQTT    mqtt;
  String  board;
  String  ntpServer;
};

class ProjectConfigurationManagement : public ConfigurationManagement {
public:
  explicit ProjectConfigurationManagement() : ConfigurationManagement("/is-cfg.json") {
  }
  virtual ~ProjectConfigurationManagement() {
  }

private:
  virtual void readProjectConfiguration(DynamicJsonDocument &data, Configuration &conf) override;
  virtual void writeProjectConfiguration(Configuration &conf, DynamicJsonDocument &data) override;
};

#endif
