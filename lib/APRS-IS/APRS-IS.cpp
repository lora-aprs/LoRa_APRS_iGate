#include "APRS-IS.h"
#include <logger.h>

void APRS_IS::setup(const String &user, const String &passcode, const String &tool_name, const String &version) {
  _user      = user;
  _passcode  = passcode;
  _tool_name = tool_name;
  _version   = version;
}

APRS_IS::ConnectionStatus APRS_IS::connect(const String &server, const int port) {
  const String login = "user " + _user + " pass " + _passcode + " vers " + _tool_name + " " + _version + "\n\r";
  return _connect(server, port, login);
}

APRS_IS::ConnectionStatus APRS_IS::connect(const String &server, const int port, const String &filter) {
  const String login = "user " + _user + " pass " + _passcode + " vers " + _tool_name + " " + _version + " filter " + filter + "\n\r";
  return _connect(server, port, login);
}

APRS_IS::ConnectionStatus APRS_IS::_connect(const String &server, const int port, const String &login_line) {
  if (!_client.connect(server.c_str(), port)) {
    return ERROR_CONNECTION;
  }
  sendMessage(login_line);
  while (true) {
    String line = _client.readStringUntil('\n');
    if (line.indexOf("logresp") != -1) {
      if (line.indexOf("unverified") == -1) {
        return SUCCESS;
      } else {
        return ERROR_PASSCODE;
      }
    }
  }
  return SUCCESS;
}

bool APRS_IS::connected() {
  return _client.connected();
}

bool APRS_IS::sendMessage(const String &message) {
  if (!connected()) {
    return false;
  }
  _client.println(message);
  return true;
}

bool APRS_IS::sendMessage(const std::shared_ptr<APRSMessage> message) {
  if (!connected()) {
    return false;
  }
  _client.println(message->encode() + "\n");
  return true;
}

int APRS_IS::available() {
  return _client.available();
}

String APRS_IS::getMessage() {
  String line;
  if (_client.available() > 0) {
    line = _client.readStringUntil('\n');
  }
  return line;
}

std::shared_ptr<APRSMessage> APRS_IS::getAPRSMessage() {
  String line;
  if (_client.available() > 0) {
    line = _client.readStringUntil('\n');
  }
  if (line.startsWith("#")) {
    return 0;
  }
  if (line.length() == 0) {
    return 0;
  }
  std::shared_ptr<APRSMessage> msg = std::shared_ptr<APRSMessage>(new APRSMessage());
  msg->decode(line);
  return msg;
}
