#include <Arduino.h>
#include <WiFiMulti.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <APRS-IS.h>
#include <APRS-Decoder.h>
#include <LoRa.h>

#include "settings.h"

WiFiMulti WiFiMulti;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, 60*60);
APRS_IS aprs_is(USER, PASS, TOOL, VERS);

void setup()
{
	Serial.begin(115200);
	delay(500);
	Serial.println("[INFO] LoRa APRS iGate by OE5BPA (Peter Buchegger)");

	WiFiMulti.addAP(WIFI_NAME, WIFI_KEY);
	Serial.print("[INFO] Waiting for WiFi");
	while(WiFiMulti.run() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(500);
	}
	Serial.println("");
	Serial.println("[INFO] WiFi connected");
	Serial.print("[INFO] IP address: ");
	Serial.println(WiFi.localIP());

	Serial.println("[INFO] Set SPI pins!");
	SPI.begin(SCK, MISO, MOSI, SS);
	LoRa.setPins(SS, RST, DIO0);
	Serial.println("[INFO] Set LoRa pins!");

	long freq = 433775000;
	Serial.print("[INFO] frequency: ");
	Serial.println(freq);
	if (!LoRa.begin(freq)) {
		Serial.println("[ERROR] Starting LoRa failed!");
		while (1);
	}
	LoRa.setSpreadingFactor(12);
	LoRa.setSignalBandwidth(125E3);
	LoRa.setCodingRate4(5);
	LoRa.enableCrc();
	Serial.println("[INFO] LoRa init done!");

	timeClient.begin();
	Serial.println("[INFO] NTP Client init done!");

	delay(500);
}

void loop()
{
	timeClient.update();
	if(WiFiMulti.run() != WL_CONNECTED)
	{
		Serial.println("[ERROR] WiFi not connected!");
		delay(1000);
		return;
	}
	if(!aprs_is.connected())
	{
		Serial.print("[INFO] connecting to server: ");
		Serial.print(SERVER);
		Serial.print(" on port: ");
		Serial.println(PORT);
		if(!aprs_is.connect(SERVER, PORT, FILTER))
		{
			Serial.println("[ERROR] Connection failed.");
			Serial.println("[INFO] Waiting 5 seconds before retrying...");
			delay(5000);
			return;
		}
		Serial.println("[INFO] Connected to server!");
	}
	if(aprs_is.available() > 0)
	{
		Serial.print("[" + timeClient.getFormattedTime() + "] ");
		Serial.println(aprs_is.getMessage());
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
	}
}
