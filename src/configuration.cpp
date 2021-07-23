#include "configuration.h"

ConfigPage page("config", "LoRa APRS iGate Config", "This is the configuration page for the LoRa APRS iGate.");

ConfigSection sGeneral(page, "general", "General", "General configuration");
ConfigSection sWifi(page, "wifi_aps", "WiFi APs", "Configuration for the WiFi access points.");
ConfigSection sBeacon(page, "beacon", "LoRa beacon", "Configuration for the LoRa beacon.");
ConfigSection sAprsIs(page, "aprs_is", "APRS IS", "Configuration for the APRS IS upload.");
ConfigSection sDigi(page, "digi", "Digi", "Configuration for the APRS digi.");
ConfigSection sLora(page, "lora", "Lora", "Configuration for the Lora interface.");
ConfigSection sDisplay(page, "display", "Display", "Configuration for the Display.");
ConfigSection sFtp(page, "ftp", "FTP", "Configuration for the FTP server.");

Configuration::Wifi::Wifi() : ssid(sWifi, "wifi_ssid", "SSID", "WiFi SSID", ""), password(sWifi, "wifi_password", "Password", "WiFi password", "") {
}

Configuration::Beacon::Beacon() : message(sBeacon, "message", "Message", "APRS message to send", "LoRa iGATE & Digi, Info: github.com/peterus/LoRa_APRS_iGate"), positionLatitude(sBeacon, "pos_lat", "Position Latitude", "The position of the iGate (latitude)", 0.0, 6), positionLongitude(sBeacon, "pos_long", "Position Longitude", "The position of the iGate (longitude)", 0.0, 6), timeout(sBeacon, "timeout", "Timeout", "The timeout to send the message (second)", 15) {
}

Configuration::APRS_IS::APRS_IS() : active(sAprsIs, "aprs_active", "active", "Activate upload to APRS IS", true), passcode(sAprsIs, "passcode", "Passcode", "The APRS IS passcode", ""), server(sAprsIs, "server", "Server", "The APRS IS server", "euro.aprs2.net"), port(sAprsIs, "port", "Port", "APRS IS port", 14580) {
}

Configuration::Digi::Digi() : active(sDigi, "digi_active", "active", "Activate digi mode", false), beacon(sDigi, "digi_beacon", "beacon", "Activate digi beacon", true) {
}

Configuration::LoRa::LoRa() : frequencyRx(sLora, "frequency_rx", "Frequency RX", "The RX frequency", 433775000), frequencyTx(sLora, "frequency_tx", "Frequency TX", "The TX frequency", 433775000), power(sLora, "power", "Power", "power in dBm", 20), spreadingFactor(sLora, "spreading_factor", "spreading factor", "", 12), signalBandwidth(sLora, "signal_bandwidth", "signal bandwidth", "", 125000), codingRate4(sLora, "coding_rate4", "coding rate 4", "", 5) {
}

Configuration::Display::Display() : alwaysOn(sDisplay, "display_always_on", "always on", "", true), timeout(sDisplay, "display_timeout", "Timeout", "", 10), overwritePin(sDisplay, "display_overwrite_pin", "overwrite pin", "", 0), turn180(sDisplay, "display_turn180", "turn 180", "", true) {
}

Configuration::Ftp::Ftp() : active(sFtp, "ftp_active", "active", "Activate ftp server", false), name(sFtp, "ftp_name", "Username", "FTP username", ""), password(sFtp, "ftp_password", "Password", "FTP password", "") {
}

Configuration::Configuration() : callsign(sGeneral, "callsign", "Callsign", "your callsign", "NOCALL-10"), board(sGeneral, "board", "Board", "you don't need to change this!", ""), ntpServer(sGeneral, "ntp_server", "NTP Server", "", "pool.ntp.org"){};
