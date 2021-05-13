#ifndef TASK_H_
#define TASK_H_

enum TaskNames
{
  TaskAprsIs = 1,
  TaskEth,
  TaskFtp,
  TaskModem,
  TaskNtp,
  TaskOta,
  TaskWifi,
  TaskSize,
};

// char const * const getTaskName(TaskNames task);

#define TASK_APRS_IS "AprsIsTask"
#define TASK_ETH     "EthTask"
#define TASK_FTP     "FTPTask"
#define TASK_MODEM   "ModemTask"
#define TASK_NTP     "NTPTask"
#define TASK_OTA     "OTATask"
#define TASK_WIFI    "WifiTask"

#endif
