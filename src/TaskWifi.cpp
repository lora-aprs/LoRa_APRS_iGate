#include <WiFi.h>
#include <logger.h>
#include "project_configuration.h"
#include "TaskWifi.h"

WifiTask::WifiTask()
	: Task("WifiTask")
{
}

WifiTask::~WifiTask()
{
}

bool WifiTask::setup(std::shared_ptr<Configuration> config)
{
	//WiFi.onEvent(WiFiEvent);
	//WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
	WiFi.setHostname(config->callsign.c_str());
	_wiFiMulti = std::shared_ptr<WiFiMulti>(new WiFiMulti());;
	for(Configuration::Wifi::AP ap : config->wifi.APs)
	{
		logPrintD("Looking for AP: ");
		logPrintlnD(ap.SSID);
		_wiFiMulti->addAP(ap.SSID.c_str(), ap.password.c_str());
	}
	logPrintlnI("Waiting for WiFi");
	//show_display("INFO", "Waiting for WiFi");
	while(_wiFiMulti->run() != WL_CONNECTED)
	{
		//show_display("INFO", "Waiting for WiFi", "....");
		delay(500);
	}
	logPrintlnI("WiFi connected");
	logPrintD("IP address: ");
	logPrintlnD(WiFi.localIP().toString());
	//show_display("INFO", "WiFi connected", "IP: ", WiFi.localIP().toString(), 2000);
	return true;
}

bool WifiTask::loop(std::shared_ptr<Configuration> config)
{
	const uint8_t wifi_status = _wiFiMulti->run();
	if(wifi_status != WL_CONNECTED)
	{
		logPrintlnE("WiFi not connected!");
		//show_display("ERROR", "WiFi not connected!");
		delay(1000);
	}
	return true;
}
