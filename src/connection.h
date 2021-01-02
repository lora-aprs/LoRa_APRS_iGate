
#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <ArduinoOTA.h>
#include <WiFiMulti.h>
#include <ESP-FTP-Server-Lib.h>
#include <FTPFilesystem.h>
#include <NTPClient.h>
#include "project_configuration.h"

bool isEthConnected();
void setup_eth();
std::shared_ptr<WiFiMulti> setup_wifi(std::shared_ptr<Configuration> config);
std::shared_ptr<ArduinoOTAClass> setup_ota(std::shared_ptr<Configuration> config);
std::shared_ptr<NTPClient> setup_ntp(std::shared_ptr<Configuration> config);
std::shared_ptr<FTPServer> setup_ftp(std::shared_ptr<Configuration> config);
std::shared_ptr<APRS_IS> setup_aprs_is(std::shared_ptr<Configuration> config);

#endif
