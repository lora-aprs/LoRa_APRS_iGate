
#ifndef SETTINGS_H_
#define SETTINGS_H_

///////////////////////////////////////////////////
///////   DON'T CHANGE THIS FILE ANYMORE!   ///////
///////////////////////////////////////////////////
///////   Use the json file in the folder   ///////
///////   'data' to configure your iGate    ///////
///////   and upload it via 'Upload File    ///////
///////   System image'! These settings     ///////
///////   will be removed soon!             ///////
///////////////////////////////////////////////////




#define WIFI_NAME ""
#define WIFI_KEY ""

#define USER "NOCALL-10"
#define PASS ""

#define SERVER "austria.aprs2.net"
//#define SERVER "euro.aprs2.net"
#define PORT 14580

#define BEACON_TIMEOUT (15)
#define BEACON_LAT_POS "4819.82N"
#define BEACON_LONG_POS "01418.68E"
#define BEACON_MESSAGE "LoRa IGATE (RX only), Info: github.com/peterus/LoRa_APRS_iGate"

//#define SEND_MESSAGES_FROM_IS_TO_LORA

#endif
