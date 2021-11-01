#include "APRSExtMessage.h"

APRSExtMessage::APRSExtMessage() {
}

/*
APRSExtMessage::APRSExtMessage(APRSExtMessage &other_msg) : _source(other_msg.getSource()), _destination(other_msg.getDestination()), _path(other_msg.getPath()), _type(other_msg.getType()), _rssi(other_msg.getRSSI()), _snr(other_msg.getSNR()), _rawBody(other_msg.getRawBody()), _body(new APRSBody()) {
  _body->setData(other_msg.getBody()->getData());
}

APRSExtMessage &APRSExtMessage::operator=(APRSExtMessage &other_msg) {
  if (this != &other_msg) {
    setSource(other_msg.getSource());
    setDestination(other_msg.getDestination());
    setPath(other_msg.getPath());
    setType(other_msg.getType());
    setRSSI(other_msg.getRSSI());
    setSNR(other_msg.getSNR());
    setother_msg.getRawBody();
    _body->setData(other_msg.getBody()->getData());
  }
  return *this;
}
*/

APRSExtMessage::~APRSExtMessage() {
}

int APRSExtMessage::getRSSI() const {
  return _rssi;
}

void APRSExtMessage::setRSSI(const int rssi) {
  _rssi = rssi;
}

float APRSExtMessage::getSNR() const {
  return _snr;
}

void APRSExtMessage::setSNR(const float snr) {
  _snr = snr;
}

String APRSExtMessage::toString()  {
  return "Source: " + getSource() + ", Destination: " + getDestination() + ", Path: " + getPath() + ", Type: " + getType().toString() + ", SNR: " + String(getSNR()) + ", RSSI: " + String(getRSSI()) + ", " + getBody()->toString();
}
