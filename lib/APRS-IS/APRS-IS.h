
#ifndef APRS_IS_Lib_h_
#define APRS_IS_Lib_h_

#include <APRS-Decoder.h>
#include <WiFi.h>

class APRS_IS {
public:
  void setup(const String &user, const String &passcode, const String &tool_name, const String &version);

  enum ConnectionStatus {
    SUCCESS,
    ERROR_CONNECTION,
    ERROR_PASSCODE,
  };

  ConnectionStatus connect(const String &server, const int port);
  ConnectionStatus connect(const String &server, const int port, const String &filter);
  bool             connected();

  bool sendMessage(const String &message);
  bool sendMessage(const std::shared_ptr<APRSMessage> message);

  int available();

  String                       getMessage();
  std::shared_ptr<APRSMessage> getAPRSMessage();

private:
  String     _user;
  String     _passcode;
  String     _tool_name;
  String     _version;
  WiFiClient _client;

  ConnectionStatus _connect(const String &server, const int port, const String &login_line);
};

#endif
