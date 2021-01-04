#include <WiFi.h>
#include <ETH.h>
#include <logger.h>
#include "TaskEth.h"
#include "Task.h"

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

EthTask::EthTask()
	: Task(TASK_ETH)
{
}

EthTask::~EthTask()
{
}

bool EthTask::setup(std::shared_ptr<Configuration> config, std::shared_ptr<BoardConfig> boardConfig)
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
	return true;
}

bool EthTask::loop(std::shared_ptr<Configuration> config)
{
	return true;
}
