#ifndef TASK_H_
#define TASK_H_

enum TaskNames {
  TaskAprsIs = 1,
  TaskEth,
  TaskFtp,
  TaskModem,
  TaskRadiolib,
  TaskNtp,
  TaskOta,
  TaskWifi,
  TaskRouter,
  TaskMQTT,
  TaskBeacon,
  TaskSize
};

#define TASK_APRS_IS  "AprsIsTask"
#define TASK_ETH      "EthTask"
#define TASK_FTP      "FTPTask"
#define TASK_MODEM    "ModemTask"
#define TASK_RADIOLIB "RadiolibTask"
#define TASK_NTP      "NTPTask"
#define TASK_OTA      "OTATask"
#define TASK_WIFI     "WifiTask"
#define TASK_ROUTER   "RouterTask"
#define TASK_MQTT     "MQTTTask"
#define TASK_BEACON   "BeaconTask"

#endif
