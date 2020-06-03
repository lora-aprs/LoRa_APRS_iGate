
#ifndef SETTINGS_H_
#define SETTINGS_H_

#define WIFI_NAME ""
#define WIFI_KEY ""

#define USER "NOCALL-10"
#define PASS ""
#define TOOL "ESP32-APRS-IS"
#define VERS "0.1"
// if FILTER is NOT active: it will use no filter on the IS server: will display just LoRa received messages as there are no messages coming from the server.
// if FILTER is active: it will be used on login on IS server and will display received messages from server. More Info: http://www.aprs-is.net/javAPRSFilter.aspx
//#define FILTER "r/48.29/14.29/25"

#define SERVER "austria.aprs2.net"
//#define SERVER "euro.aprs2.net"
#define PORT 14580

#define BEACON_TIMEOUT (15)
#define BEACON_LAT_POS "4819.82N"
#define BEACON_LONG_POS "01418.68E"
#define BEACON_MESSAGE "LoRa IGATE (RX only), Info: github.com/peterus/LoRa_APRS_iGate"

#define LORA_FREQUENCY (433775000)
#define LORA_SPREADING_FACTOR (12)
#define LORA_SIGNAL_BANDWIDTH (125E3)
#define LORA_CODING_RATE4 (5)

//#define ARDUINO_T_Beam_V0_7

#endif
