#ifndef PROJECT_CONFIGURATION_H_
#define PROJECT_CONFIGURATION_H_

#include "configuration.h"

class Configuration
{
public:
	class Wifi
	{
	public:
		class AP
		{
		public:
			String SSID;
			String password;
		};

		Wifi() : active(false) {}

		bool active;
		std::list<AP> APs;
	};

	class Beacon
	{
	public:
		Beacon() : message("LoRa iGATE & Digi, Info: github.com/peterus/LoRa_APRS_iGate"), positionLatitude(0.0), positionLongitude(0.0) {}

		String message;
		double positionLatitude;
		double positionLongitude;
	};

	class APRS_IS
	{
	public:
		APRS_IS() : active(false), server("euro.aprs2.net"), port(14580), beacon(true), beaconTimeout(15) {}

		bool active;
		String password;
		String server;
		int port;
		bool beacon;
		int beaconTimeout;
	};

	class LoRa
	{
	public:
		LoRa() : frequencyRx(433775000), frequencyTx(433775000), power(20), spreadingFactor(12), signalBandwidth(125000), codingRate4(5) {}

		long frequencyRx;
		long frequencyTx;
		int power;
		int spreadingFactor;
		long signalBandwidth;
		int codingRate4;
	};

	class Display
	{
	public:
		Display() : alwaysOn(true), timeout(10), overwritePin(0) {}

		bool alwaysOn;
		int timeout;
		int overwritePin;
	};

	class Ftp
	{
	public:
		class User
		{
		public:
			String name;
			String password;
		};

		Ftp() : active(false) {}

		bool active;
		std::list<User> users;
	};

	Configuration() : callsign("NOCALL-10"), board(""), ntpServer("pool.ntp.org") {};

	String callsign;
	Wifi wifi;
	Beacon beacon;
	APRS_IS aprs_is;
	LoRa lora;
	Display display;
	Ftp ftp;
	String board;
	String ntpServer;
};

class ProjectConfigurationManagement : public ConfigurationManagement
{
public:
	explicit ProjectConfigurationManagement() : ConfigurationManagement("/is-cfg.json") {}
	virtual ~ProjectConfigurationManagement() {}

private:
	virtual Configuration * readProjectConfiguration(DynamicJsonDocument & data) override;
	virtual void writeProjectConfiguration(Configuration * conf, DynamicJsonDocument & data) override;
};

#endif
