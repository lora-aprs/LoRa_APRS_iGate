
#ifndef SETTINGS_H_
#define SETTINGS_H_

#define WIFI_NAME ""
#define WIFI_KEY ""

#define USER "OE5BPA-10"
#define PASS ""
#define TOOL "ESP32-APRS-IS"
#define VERS "0.1"
#define FILTER "r/48.29/14.29/25"

#define SERVER "austria.aprs2.net"
//#define SERVER "euro.aprs2.net"
#define PORT 14580

// LoRa Pins:
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

#define BROADCAST_TIMEOUT 15
#define BROADCAST_MESSAGE "OE5BPA-10>APRS:=4819.82NI01418.68E&LoRa IGATE (test RX mode), Info: github.com/peterus/LoRa_APRS_iGate"

String call = "OE5BPA";

#endif
