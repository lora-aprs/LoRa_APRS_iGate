
#include <Arduino.h>
#include <ETH.h>
#include <SPIFFS.h>
#include <logger.h>
#include <TimeLib.h>
#include <APRS-IS.h>

#include "connection.h"

volatile bool eth_connected = false;

static void WiFiEvent(WiFiEvent_t event)
{
	switch (event) {
	case SYSTEM_EVENT_ETH_START:
		logPrintlnI("ETH Started");
		ETH.setHostname("esp32-ethernet");
		break;
	case SYSTEM_EVENT_ETH_CONNECTED:
		logPrintlnI("ETH Connected");
		break;
	case SYSTEM_EVENT_ETH_GOT_IP:
		logPrintI("ETH MAC: ");
		logPrintI(ETH.macAddress());
		logPrintI(", IPv4: ");
		logPrintI(ETH.localIP().toString());
		if (ETH.fullDuplex()) {
			logPrintI(", FULL_DUPLEX");
		}
		logPrintI(", ");
		logPrintI(String(ETH.linkSpeed()));
		logPrintlnI("Mbps");
		eth_connected = true;
		break;
	case SYSTEM_EVENT_ETH_DISCONNECTED:
		logPrintlnW("ETH Disconnected");
		eth_connected = false;
		break;
	case SYSTEM_EVENT_ETH_STOP:
		logPrintlnW("ETH Stopped");
		eth_connected = false;
		break;
	default:
		break;
	}
}

bool isEthConnected()
{
	return eth_connected;
}

void setup_eth()
{
	WiFi.onEvent(WiFiEvent);

	#define ETH_POWER_PIN	-1
	#define ETH_TYPE		ETH_PHY_LAN8720
	#define ETH_ADDR		0
	#define ETH_MDC_PIN		23
	#define ETH_MDIO_PIN	18
	#define ETH_NRST		5
	#define ETH_CLK			ETH_CLOCK_GPIO17_OUT	// TTGO PoE V1.0
	//#define ETH_CLK			ETH_CLOCK_GPIO0_OUT		// TTGO PoE V1.2

	pinMode(ETH_NRST, OUTPUT);
	digitalWrite(ETH_NRST, 0);
	delay(200);
	digitalWrite(ETH_NRST, 1);
	delay(200);
	digitalWrite(ETH_NRST, 0);
	delay(200);
	digitalWrite(ETH_NRST, 1);

	ETH.begin(ETH_ADDR, ETH_POWER_PIN, ETH_MDC_PIN, ETH_MDIO_PIN, ETH_TYPE, ETH_CLK);
	while(!eth_connected)
	{
		sleep(1);
	}
}

std::shared_ptr<WiFiMulti> setup_wifi(std::shared_ptr<Configuration> config)
{
	WiFi.onEvent(WiFiEvent);
	//WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
	WiFi.setHostname(config->callsign.c_str());
	std::shared_ptr<WiFiMulti> wiFiMulti = std::shared_ptr<WiFiMulti>(new WiFiMulti());;
	for(Configuration::Wifi::AP ap : config->wifi.APs)
	{
		logPrintD("Looking for AP: ");
		logPrintlnD(ap.SSID);
		wiFiMulti->addAP(ap.SSID.c_str(), ap.password.c_str());
	}
	logPrintlnI("Waiting for WiFi");
	//show_display("INFO", "Waiting for WiFi");
	while(wiFiMulti->run() != WL_CONNECTED)
	{
		//show_display("INFO", "Waiting for WiFi", "....");
		delay(500);
	}
	logPrintlnI("WiFi connected");
	logPrintD("IP address: ");
	logPrintlnD(WiFi.localIP().toString());
	//show_display("INFO", "WiFi connected", "IP: ", WiFi.localIP().toString(), 2000);
	return wiFiMulti;
}

std::shared_ptr<ArduinoOTAClass> setup_ota(std::shared_ptr<Configuration> config)
{
	std::shared_ptr<ArduinoOTAClass> ota = std::shared_ptr<ArduinoOTAClass>(new ArduinoOTAClass());
	ota->onStart([&]()
		{
			String type;
			if (ota->getCommand() == U_FLASH)
				type = "sketch";
			else // U_SPIFFS
				type = "filesystem";
			logPrintlnI("Start updating " + type);
			//show_display("OTA UPDATE", "Start update", type);
		})
		.onEnd([]()
		{
			logPrintlnI("");
			logPrintlnI("OTA End");
		})
		.onProgress([](unsigned int progress, unsigned int total)
		{
			logPrintI("Progress: ");
			logPrintI(String(progress / (total / 100)));
			logPrintlnI("%");
			//show_display("OTA UPDATE", "Progress: ", String(progress / (total / 100)) + "%");
		})
		.onError([](ota_error_t error)
		{
			logPrintE("Error[");
			logPrintE(String(error));
			logPrintE("]: ");
			if (error == OTA_AUTH_ERROR) logPrintlnE("Auth Failed");
			else if (error == OTA_BEGIN_ERROR) logPrintlnE("Begin Failed");
			else if (error == OTA_CONNECT_ERROR) logPrintlnE("Connect Failed");
			else if (error == OTA_RECEIVE_ERROR) logPrintlnE("Receive Failed");
			else if (error == OTA_END_ERROR) logPrintlnE("End Failed");
		});
	ota->setHostname(config->callsign.c_str());
	ota->begin();
	logPrintlnI("OTA init done!");
	return ota;
}

std::shared_ptr<NTPClient> setup_ntp(std::shared_ptr<Configuration> config)
{
	std::shared_ptr<NTPClient> ntpClient = std::shared_ptr<NTPClient>(new NTPClient(config->ntpServer.c_str()));
	ntpClient->begin();
	while(!ntpClient->forceUpdate())
	{
		logPrintlnW("NTP Client force update issue! Waiting 1 sek...");
		logPrintlnD(ntpClient->getFormattedTime());
		//show_display("WARN", "NTP Client force update issue! Waiting 1 sek...", 1000);
		sleep(1);
	}
	setTime(ntpClient->getEpochTime());
	logPrintlnI("NTP Client init done!");
	//show_display("INFO", "NTP Client init done!", 2000);
	return ntpClient;
}

std::shared_ptr<FTPServer> setup_ftp(std::shared_ptr<Configuration> config)
{
	std::shared_ptr<FTPServer> ftpServer = std::shared_ptr<FTPServer>(new FTPServer());
	if(config->ftp.active)
	{
		for(Configuration::Ftp::User user : config->ftp.users)
		{
			logPrintD("Adding user to FTP Server: ");
			logPrintlnD(user.name);
			ftpServer->addUser(user.name, user.password);
		}
		ftpServer->addFilesystem("SPIFFS", &SPIFFS);
		ftpServer->begin();
		logPrintlnI("FTP Server init done!");
	}
	return ftpServer;
}

std::shared_ptr<APRS_IS> setup_aprs_is(std::shared_ptr<Configuration> config)
{
	std::shared_ptr<APRS_IS> aprs_is = std::shared_ptr<APRS_IS>(new APRS_IS(config->callsign, config->aprs_is.passcode , "ESP32-APRS-IS", "0.1"));
	logPrintI("connecting to APRS-IS server: ");
	logPrintI(config->aprs_is.server);
	logPrintI(" on port: ");
	logPrintlnI(String(config->aprs_is.port));
	//show_display("INFO", "Connecting to APRS-IS server");
	while(!aprs_is->connect(config->aprs_is.server, config->aprs_is.port))
	{
		logPrintlnE("Connection failed.");
		logPrintlnI("Waiting 1 seconds before retrying...");
		//show_display("ERROR", "Server connection failed!", "waiting 5 sec");
		delay(1000);
	}
	logPrintlnI("Connected to APRS-IS server!");
	return aprs_is;
}
