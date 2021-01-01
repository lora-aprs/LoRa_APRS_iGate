#ifndef LORA_H_
#define LORA_H_

#include <memory>
#include <Arduino.h>
#include <LoRa.h>
#include <APRS-Decoder.h>
#include <SignalSlot.h>

#define LORA_RX_FREQUENCY (433775000)
#define LORA_TX_FREQUENCY (433900000)
#define LORA_SPREADING_FACTOR (12)
#define LORA_SIGNAL_BANDWIDTH (125E3)
#define LORA_CODING_RATE4 (5)

class LoRa_APRS : public LoRaClass, public Slot1<const std::shared_ptr<APRSMessage>>, public Signal3<std::shared_ptr<APRSMessage>, int, float>
{
public:
	explicit LoRa_APRS(std::shared_ptr<BoardConfig> boardConfig);
	
	bool checkMessage();
	std::shared_ptr<APRSMessage> getMessage();

	void sendMessage(const std::shared_ptr<APRSMessage> msg);

	void setRxFrequency(long frequency);
	long getRxFrequency() const;

	void setTxFrequency(long frequency);
	long getTxFrequency() const;

	void action(const std::shared_ptr<APRSMessage> elem) override;

private:
	std::shared_ptr<APRSMessage> _LastReceivedMsg;
	long _RxFrequency;
	long _TxFrequency;
};

#endif
