#include <map>

#include <logger.h>
#include <APRS-IS.h>

#include <TimeLib.h>
#include "SignalSlot.h"
#include "BoardFinder.h"
#include "LoRa_APRS.h"
#include "display.h"
#include "power_management.h"
#include "project_configuration.h"
#include "connection.h"

HardwareSerial Serial(0);

std::shared_ptr<ArduinoOTAClass> OTA;
std::shared_ptr<PowerManagement> powerManagement;
std::shared_ptr<WiFiMulti> WiFiMulti;
std::shared_ptr<NTPClient> ntpClient;
std::shared_ptr<FTPServer> ftpServer;
std::shared_ptr<Configuration> userConfig;
std::shared_ptr<BoardConfig> boardConfig;
std::shared_ptr<APRS_IS> aprs_is;
std::shared_ptr<LoRa_APRS> lora_aprs;
std::shared_ptr<APRSMessage> BeaconMsg;

String create_lat_aprs(double lat);
String create_long_aprs(double lng);

std::shared_ptr<LoRa_APRS> setup_lora();

PrintMessageToConsole printMessageConsole;
bool ethEnabled = false;

// cppcheck-suppress unusedFunction
void setup()
{
	Serial.begin(115200);
	Logger::instance().setSerial(&Serial);
	delay(500);

	ProjectConfigurationManagement confmg;
	userConfig = confmg.readConfiguration();

	std::list<std::shared_ptr<BoardConfig>> boardConfigs;
	boardConfigs.push_back(std::shared_ptr<BoardConfig>(new BoardConfig("TTGO_LORA32_V1",         eTTGO_LORA32_V1,          4, 15, 0x3C,  0,  5, 19, 27, 18, 14, 26)));
	boardConfigs.push_back(std::shared_ptr<BoardConfig>(new BoardConfig("TTGO_LORA32_V2",         eTTGO_LORA32_V2,         21, 22, 0x3C,  0,  5, 19, 27, 18, 14, 26, true)));
	boardConfigs.push_back(std::shared_ptr<BoardConfig>(new BoardConfig("TTGO_T_Beam_V0_7",       eTTGO_T_Beam_V0_7,       21, 22, 0x3C,  0,  5, 19, 27, 18, 14, 26, true)));
	boardConfigs.push_back(std::shared_ptr<BoardConfig>(new BoardConfig("TTGO_T_Beam_V1_0",       eTTGO_T_Beam_V1_0,       21, 22, 0x3C,  0,  5, 19, 27, 18, 14, 26, true, true)));
	boardConfigs.push_back(std::shared_ptr<BoardConfig>(new BoardConfig("ETH_BOARD",              eETH_BOARD,              33, 32, 0x3C,  0, 14,  2, 15, 12,  4, 36)));
	boardConfigs.push_back(std::shared_ptr<BoardConfig>(new BoardConfig("TRACKERD",               eTRACKERD,                5,  4, 0x3C,  0, 18, 19, 23, 16, 14, 26)));
	boardConfigs.push_back(std::shared_ptr<BoardConfig>(new BoardConfig("HELTEC_WIFI_LORA_32_V1", eHELTEC_WIFI_LORA_32_V1,  4, 15, 0x3C, 16,  5, 19, 27, 18, 14, 26)));
	boardConfigs.push_back(std::shared_ptr<BoardConfig>(new BoardConfig("HELTEC_WIFI_LORA_32_V2", eHELTEC_WIFI_LORA_32_V2,  4, 15, 0x3C, 16,  5, 19, 27, 18, 14, 26)));

	BoardFinder finder(boardConfigs);
	boardConfig = finder.getBoardConfig(userConfig->board);
	if(boardConfig == 0)
	{
		boardConfig = finder.searchBoardConfig();
		if(boardConfig == 0)
		{
			logPrintlnE("Board config not set and search failed!");
			while(true)
			{}
		}
		userConfig->board = boardConfig->Name;
		confmg.writeConfiguration(userConfig);
		logPrintlnI("will restart board now!");
		ESP.restart();
	}
	logPrintI("Board ");
	logPrintI(boardConfig->Name);
	logPrintlnI(" loaded.");

	if(boardConfig->Type == eTTGO_T_Beam_V1_0)
	{
		TwoWire wire(0);
		wire.begin(boardConfig->OledSda, boardConfig->OledScl);
		std::shared_ptr<PowerManagement> powerManagement = std::shared_ptr<PowerManagement>(new PowerManagement);
		if (!powerManagement->begin(wire))
		{
			logPrintlnI("AXP192 init done!");
		}
		else
		{
			logPrintlnE("AXP192 init failed!");
		}
		powerManagement->activateLoRa();
		powerManagement->activateOLED();
		powerManagement->deactivateGPS();
	}

	logPrintlnW("LoRa APRS iGate by OE5BPA (Peter Buchegger)");
	logPrintlnW("Version: 20.49.0-dev");
	setup_display(boardConfig);
	show_display("OE5BPA", "LoRa APRS iGate", "by Peter Buchegger", "20.49.0-dev", 3000);

	load_config(boardConfig);
	lora_aprs = setup_lora();
	if(boardConfig->Type == eETH_BOARD)
	{
		setup_eth();
		ethEnabled = true;
	}
	WiFiMulti = setup_wifi(userConfig);
	OTA = setup_ota(userConfig);
	ntpClient = setup_ntp(userConfig);
	ftpServer = setup_ftp(userConfig);
	aprs_is = std::shared_ptr<APRS_IS>(new APRS_IS(userConfig->callsign, userConfig->aprs_is.password , "ESP32-APRS-IS", "0.1"));

	if(userConfig->display.overwritePin != 0)
	{
		pinMode(userConfig->display.overwritePin, INPUT);
		pinMode(userConfig->display.overwritePin, INPUT_PULLUP);
	}

	logPrintlnD("connect objects...");
	lora_aprs->connectSlot(&printMessageConsole);
	lora_aprs->connectSlot(aprs_is.get());

	delay(500);
	logPrintlnI("setup done...");
}

// cppcheck-suppress unusedFunction
void loop()
{
	static bool beacon_aprs_is = true;
	if(userConfig->ftp.active)
	{
		ftpServer->handle();
		static bool configWasOpen = false;
		if(configWasOpen && ftpServer->countConnections() == 0)
		{
			logPrintlnW("Maybe the config has been changed via FTP, lets restart now to get the new config...");
			Serial.println();
			ESP.restart();
		}
		if(ftpServer->countConnections() > 0)
		{
			configWasOpen = true;
		}
	}

	const uint8_t wifi_status = WiFiMulti->run();
	if(!ethEnabled && wifi_status != WL_CONNECTED)
	{
		logPrintlnE("WiFi not connected!");
		show_display("ERROR", "WiFi not connected!");
		delay(1000);
		return;
	}

	OTA->handle();
	if(ntpClient->update())
	{
		setTime(ntpClient->getEpochTime());
	}

	if(!aprs_is->connected())
	{
		logPrintI("connecting to APRS-IS server: ");
		logPrintI(userConfig->aprs_is.server);
		logPrintI(" on port: ");
		logPrintlnI(String(userConfig->aprs_is.port));
		show_display("INFO", "Connecting to APRS-IS server");
		if(!aprs_is->connect(userConfig->aprs_is.server, userConfig->aprs_is.port))
		{
			logPrintlnE("Connection failed.");
			logPrintlnI("Waiting 5 seconds before retrying...");
			show_display("ERROR", "Server connection failed!", "waiting 5 sec");
			delay(5000);
			return;
		}
		logPrintlnI("Connected to APRS-IS server!");
	}

	aprs_is->getAPRSMessage();
	lora_aprs->checkMessage();
	
	if(false) //beacon_aprs_is
	{
		beacon_aprs_is = false;
		show_display(userConfig->callsign, "Beacon to APRS-IS Server...");
		logPrintD("[" + ntpClient->getFormattedTime() + "] ");
		logPrintlnD(BeaconMsg->encode());
		aprs_is->sendMessage(BeaconMsg);
		show_display(userConfig->callsign, "Standby...");
	}
}

std::shared_ptr<LoRa_APRS> setup_lora()
{
	std::shared_ptr<LoRa_APRS> lora_aprs = std::shared_ptr<LoRa_APRS>(new LoRa_APRS(boardConfig));
	if(!lora_aprs->begin(lora_aprs->getRxFrequency()))
	{
		logPrintlnE("Starting LoRa failed!");
		show_display("ERROR", "Starting LoRa failed!");
		while(true);
	}
	lora_aprs->setRxFrequency(userConfig->lora.frequencyRx);
	lora_aprs->setTxFrequency(userConfig->lora.frequencyTx);
	lora_aprs->setTxPower(userConfig->lora.power);
	lora_aprs->setSpreadingFactor(userConfig->lora.spreadingFactor);
	lora_aprs->setSignalBandwidth(userConfig->lora.signalBandwidth);
	lora_aprs->setCodingRate4(userConfig->lora.codingRate4);
	lora_aprs->enableCrc();
	logPrintlnI("LoRa init done!");
	show_display("INFO", "LoRa init done!", 2000);

	BeaconMsg = std::shared_ptr<APRSMessage>(new APRSMessage());
	BeaconMsg->setSource(userConfig->callsign);
	BeaconMsg->setDestination("APLG0");
	String lat = create_lat_aprs(userConfig->beacon.positionLatitude);
	String lng = create_long_aprs(userConfig->beacon.positionLongitude);
	BeaconMsg->getAPRSBody()->setData(String("=") + lat + "I" + lng + "&" + userConfig->beacon.message);

	return lora_aprs;
}

String create_lat_aprs(double lat)
{
	char str[20];
	char n_s = 'N';
	if(lat < 0)
	{
		n_s = 'S';
	}
	lat = std::abs(lat);
	sprintf(str, "%02d%05.2f%c", (int)lat, (lat - (double)((int)lat)) * 60.0, n_s);
	String lat_str(str);
	return lat_str;
}

String create_long_aprs(double lng)
{
	char str[20];
	char e_w = 'E';
	if(lng < 0)
	{
		e_w = 'W';
	}
	lng = std::abs(lng);
	sprintf(str, "%03d%05.2f%c", (int)lng, (lng - (double)((int)lng)) * 60.0, e_w);
	String lng_str(str);
	return lng_str;
}
