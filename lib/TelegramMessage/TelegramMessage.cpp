#include <logger.h>

#include "TelegramMessage.h"
#include <TimeLib.h>

TelegramMessage::TelegramMessage() : _body(new TelegramBody()) {
}

TelegramMessage::TelegramMessage(TelegramMessage &other_msg) : _time(other_msg.getTime()), _body(new TelegramBody()) {
  _body->setData(other_msg.getBody()->getData());
}

TelegramMessage &TelegramMessage::operator=(TelegramMessage &other_msg) {
  if (this != &other_msg) {
    _time = other_msg.getTime();
    _body->setData(other_msg.getBody()->getData());
  }
  return *this;
}

TelegramMessage::~TelegramMessage() {
  if (_body != 0) {
    delete _body;
  }
}

unsigned long TelegramMessage::getTime() const {
  return _time;
}

void TelegramMessage::setTime(const unsigned long &time) {
  _time = time;
}

TelegramBody *const TelegramMessage::getBody() {
  return _body;
}

String TelegramMessage::toString() const {
  return timeString(_time) + " (UTC), " + _body->toString();
}

TelegramBody::TelegramBody() {
}

TelegramBody::~TelegramBody() {
}

String TelegramBody::getData() const {
  return _data;
}

void TelegramBody::setData(const String &data) {
  _data = data;
}

String TelegramBody::toString() const {
  return "Data: " + _data;
}
