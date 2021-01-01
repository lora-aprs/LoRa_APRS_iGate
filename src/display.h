
#ifndef DISPLAY_H_
#define DISPLAY_H_

void setup_display(std::shared_ptr<BoardConfig> boardConfig);
void turn_off_display();

void show_display(String header, int wait = 0);
void show_display(String header, String line1, int wait = 0);
void show_display(String header, String line1, String line2, int wait = 0);
void show_display(String header, String line1, String line2, String line3, int wait = 0);
void show_display(String header, String line1, String line2, String line3, String line4, int wait = 0);
void show_display(String header, String line1, String line2, String line3, String line4, String line5, int wait = 0);

#include <APRSMessage.h>
#include "SignalSlot.h"
#include "TimeLib.h"
#include "logger.h"

class PrintMessageToConsole : public Slot1<std::shared_ptr<APRSMessage>>, public Slot3<std::shared_ptr<APRSMessage>, int, float>
{
public:
	void action(std::shared_ptr<APRSMessage> msg, int rssi, float snr) override
	{
		//setup_display(boardConfig); secondsSinceDisplay = 0; //display_is_on = true;
		//show_display(Config->callsign, timeClient->getFormattedTime() + "         LoRa", "RSSI: " + String(lora_aprs->packetRssi()) + ", SNR: " + String(lora_aprs->packetSnr()), elem->toString());
		logPrintD("[" + timeString() + "] ");
		logPrintD("Received packet '");
		logPrintD(msg->toString());
		logPrintD("' with RSSI ");
		logPrintD(String(rssi));
		logPrintD(" and SNR ");
		logPrintlnD(String(snr));
	}

	void action(std::shared_ptr<APRSMessage> msg) override
	{
		//setup_display(boardConfig); secondsSinceDisplay = 0; //display_is_on = true;
		//show_display(Config->callsign, timeClient->getFormattedTime() + "         LoRa", "RSSI: " + String(lora_aprs->packetRssi()) + ", SNR: " + String(lora_aprs->packetSnr()), elem->toString());
		logPrintD("[" + timeString() + "] ");
		logPrintD("Received packet '");
		logPrintD(msg->toString());
		logPrintD("'");
	}
};

#endif
