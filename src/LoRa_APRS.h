#ifndef LORA_H_
#define LORA_H_

#include <memory>
#include <Arduino.h>
#include <LoRa.h>
#include <APRS-Decoder.h>

#define LORA_RX_FREQUENCY (433775000)
#define LORA_TX_FREQUENCY (433900000)
#define LORA_SPREADING_FACTOR (12)
#define LORA_SIGNAL_BANDWIDTH (125E3)
#define LORA_CODING_RATE4 (5)

class LoRa_APRS
{
public:
    LoRa_APRS();
    bool begin();
    
    bool hasMessage();
    std::shared_ptr<APRSMessage> getMessage();
    int getMessageRssi();
    float getMessageSnr();

    void sendMessage(const std::shared_ptr<APRSMessage> msg);

    // settings:
    long rx_frequency;
    long tx_frequency;
    int spreadingfactor;
    long signalbandwidth;
    int codingrate4;

private:
    std::shared_ptr<APRSMessage> _LastReceivedMsg;
};

#endif
