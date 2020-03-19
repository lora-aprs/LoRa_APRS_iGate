#include <Arduino.h>
#include <WiFiMulti.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <APRS-IS.h>
#include <APRS-Decoder.h>
#include <LoRa.h>

#include "settings.h"
#include "display.h"

WiFiMulti WiFiMulti;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, 60*60);
APRS_IS aprs_is(USER, PASS, TOOL, VERS);

int next_update = -1;

void setup()
{
	Serial.begin(115200);
	init_display();
	
	delay(500);
	Serial.println("[INFO] LoRa APRS iGate by OE5BPA (Peter Buchegger)");
	show_display_2("OE5BPA", "LoRa APRS iGate", "by Peter Buchegger", 2000);

	WiFi.setHostname("LoRa_APRS_iGate");
	WiFiMulti.addAP(WIFI_NAME, WIFI_KEY);
	Serial.print("[INFO] Waiting for WiFi");
	show_display_1("INFO", "Waiting for WiFi");
	while(WiFiMulti.run() != WL_CONNECTED)
	{
		Serial.print(".");
		show_display_2("INFO", "Waiting for WiFi", "....");
		delay(500);
	}
	Serial.println("");
	Serial.println("[INFO] WiFi connected");
	Serial.print("[INFO] IP address: ");
	Serial.println(WiFi.localIP());
	show_display_3("INFO", "WiFi connected", "IP: ", WiFi.localIP().toString(), 2000);

	ArduinoOTA
		.onStart([]()
		{
			String type;
			if (ArduinoOTA.getCommand() == U_FLASH)
				type = "sketch";
			else // U_SPIFFS
				type = "filesystem";
			Serial.println("Start updating " + type);
		})
		.onEnd([]()
		{
			Serial.println("\nEnd");
		})
		.onProgress([](unsigned int progress, unsigned int total)
		{
			Serial.printf("Progress: %u%%\r\n", (progress / (total / 100)));
		})
		.onError([](ota_error_t error) {
			Serial.printf("Error[%u]: ", error);
			if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
			else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
			else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
			else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
			else if (error == OTA_END_ERROR) Serial.println("End Failed");
		});
	ArduinoOTA.begin();

	Serial.println("[INFO] Set SPI pins!");
	SPI.begin(SCK, MISO, MOSI, SS);
	LoRa.setPins(SS, RST, DIO0);
	Serial.println("[INFO] Set LoRa pins!");

	long freq = 433775000;
	Serial.print("[INFO] frequency: ");
	Serial.println(freq);
	if (!LoRa.begin(freq)) {
		Serial.println("[ERROR] Starting LoRa failed!");
		show_display_1("ERROR", "Starting LoRa failed!");
		while (1);
	}
	LoRa.setSpreadingFactor(12);
	LoRa.setSignalBandwidth(125E3);
	LoRa.setCodingRate4(5);
	LoRa.enableCrc();
	Serial.println("[INFO] LoRa init done!");
	show_display_1("INFO", "LoRa init done!", 2000);

	timeClient.begin();
	if(!timeClient.forceUpdate())
	{
		Serial.println("[WARN] NTP Client force update issue!");
		show_display_1("WARN", "NTP Client force update issue!", 2000);
	}
	Serial.println("[INFO] NTP Client init done!");
	show_display_1("INFO", "NTP Client init done!", 2000);

	delay(500);
}

void loop()
{
	timeClient.update();
	ArduinoOTA.handle();
	if(WiFiMulti.run() != WL_CONNECTED)
	{
		Serial.println("[ERROR] WiFi not connected!");
		show_display_1("ERROR", "WiFi not connected!");
		delay(1000);
		return;
	}
	if(!aprs_is.connected())
	{
		Serial.print("[INFO] connecting to server: ");
		Serial.print(SERVER);
		Serial.print(" on port: ");
		Serial.println(PORT);
		//show_display_3("INFO", "Connecting to server", SERVER, PORT, 2000);
		show_display_1("INFO", "Connecting to server");
		if(!aprs_is.connect(SERVER, PORT, FILTER))
		{
			Serial.println("[ERROR] Connection failed.");
			Serial.println("[INFO] Waiting 5 seconds before retrying...");
			show_display_2("ERROR", "Server connection failed!", "waiting 5 sec");
			delay(5000);
			return;
		}
		Serial.println("[INFO] Connected to server!");
	}
	if(next_update == timeClient.getMinutes() || next_update == -1)
	{
		show_display_1(call, "Broadcast to Server...");
		Serial.print("[" + timeClient.getFormattedTime() + "] ");
		aprs_is.sendMessage(BROADCAST_MESSAGE);
		next_update = (timeClient.getMinutes() + BROADCAST_TIMEOUT) % 60;
	}
	if(aprs_is.available() > 0)
	{
		String str = aprs_is.getMessage();
		Serial.print("[" + timeClient.getFormattedTime() + "] ");
		Serial.println(str);
		show_display_2(call, timeClient.getFormattedTime(), str, 0);
	}
	int packetSize = LoRa.parsePacket();
	if(packetSize)
	{
		String str;
		Serial.print("[" + timeClient.getFormattedTime() + "] ");
		Serial.print(" Received packet '");
		while(LoRa.available())
		{
			str += (char)LoRa.read();
		}
		Serial.print(str);
		Serial.print("' with RSSI ");
		Serial.print(LoRa.packetRssi());
		Serial.print(" and SNR ");
		Serial.println(LoRa.packetSnr());

		/*APRSMessage msg;
		msg.decode(str);
		Serial.print("[INFO] ");
		Serial.println(msg.toString());*/
		aprs_is.sendMessage(str);

		show_display_4(call, timeClient.getFormattedTime(), "RSSI: " + String(LoRa.packetRssi()), "SNR: " + String(LoRa.packetSnr()), str, 0);
	}
}
