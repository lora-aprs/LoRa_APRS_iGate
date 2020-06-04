#include <LoRa_APRS.h>

LoRa_APRS::LoRa_APRS()
    : rx_frequency(LORA_RX_FREQUENCY), tx_frequency(LORA_TX_FREQUENCY), spreadingfactor(LORA_SPREADING_FACTOR),
      signalbandwidth(LORA_SIGNAL_BANDWIDTH), codingrate4(LORA_CODING_RATE4), _LastReceivedMsg(0)
{
	SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
	LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);
}

bool LoRa_APRS::begin()
{
	if (!LoRa.begin(rx_frequency))
    {
        return false;
	}
	LoRa.setSpreadingFactor(spreadingfactor);
	LoRa.setSignalBandwidth(signalbandwidth);
	LoRa.setCodingRate4(codingrate4);
	LoRa.enableCrc();
    return true;
}

bool LoRa_APRS::hasMessage()
{
	if(!LoRa.parsePacket())
	{
        return false;
    }
    // read header:
    char dummy[4];
    LoRa.readBytes(dummy, 3);
    if(dummy[0] != '<')
    {
        // is no APRS message, ignore message
        while(LoRa.available())
        {
            LoRa.read();
        }
        return false;
    }
    // read APRS data:
    String str;
    while(LoRa.available())
    {
        str += (char)LoRa.read();
    }
    _LastReceivedMsg = std::shared_ptr<APRSMessage>(new APRSMessage());
    _LastReceivedMsg->decode(str);
    return true;
}

std::shared_ptr<APRSMessage> LoRa_APRS::getMessage()
{
    return _LastReceivedMsg;
}

int LoRa_APRS::getMessageRssi()
{
    return LoRa.packetRssi();
}

float LoRa_APRS::getMessageSnr()
{
    return LoRa.packetSnr();
}

// cppcheck-suppress unusedFunction
void LoRa_APRS::sendMessage(const std::shared_ptr<APRSMessage> msg)
{
    LoRa.setFrequency(tx_frequency);
    String data = msg->encode();
    LoRa.beginPacket();
    // Header:
    LoRa.write('<');
    LoRa.write(0xFF);
    LoRa.write(0x01);
    // APRS Data:
    LoRa.write((const uint8_t *)data.c_str(), data.length());
    LoRa.endPacket();
    LoRa.setFrequency(rx_frequency);
}
