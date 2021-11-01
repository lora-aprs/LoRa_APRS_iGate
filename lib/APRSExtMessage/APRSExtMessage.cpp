#include "APRSExtMessage.h"

APRSExtMessage::APRSExtMessage() : _body(new APRSBody()) {
}

APRSExtMessage::APRSExtMessage(APRSExtMessage &other_msg) : _source(other_msg.getSource()), _destination(other_msg.getDestination()), _path(other_msg.getPath()), _type(other_msg.getType()), _rssi(other_msg.getRSSI()), _snr(other_msg.getSNR()), _rawBody(other_msg.getRawBody()), _body(new APRSBody()) {
  _body->setData(other_msg.getBody()->getData());
}

APRSExtMessage &APRSExtMessage::operator=(APRSExtMessage &other_msg) {
  if (this != &other_msg) {
    _source      = other_msg.getSource();
    _destination = other_msg.getDestination();
    _path        = other_msg.getPath();
    _type        = other_msg.getType();
    _rssi        = other_msd.getRSSI();
    _snr         = other_msd.getSNR();
    _rawBody     = other_msg.getRawBody();
    _body->setData(other_msg.getBody()->getData());
  }
  return *this;
}

APRSExtMessage::~APRSExtMessage() {
}

float APRSExtMessage::getRSSI() const {
  return _rssi;
}

void APRSExtMessage::setRSSI(const int rssi) {
  _path = rssi;
}

float APRSExtMessage::getSNR() const {
  return _snr;
}

void APRSExtMessage::setSNR(const float snr) {
  _snr = snr;
}

String APRSExtMessage::toString() const {
  return "Source: " + _source + ", Destination: " + _destination + ", Path: " + _path + ", Type: " + _type.toString() + ", SNR: " + String(_snr) + ", RSSI: " + String(_rssi) + ", " + _body->toString();
}
