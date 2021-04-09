#include "Timer.h"

Timer::Timer() : _timeout_ms(0), _nextTimeout(0) {
}

void Timer::setTimeout(const uint32_t timeout_ms) {
  _timeout_ms = timeout_ms;
}

time_t Timer::getTriggerTimeInSec() const {
  return (_nextTimeout - millis()) / 1000;
}

bool Timer::isActive() const {
  return _nextTimeout != 0;
}

void Timer::reset() {
  _nextTimeout = 0;
}

bool Timer::check() {
  return millis() > _nextTimeout;
}

void Timer::start() {
  _nextTimeout = millis() + _timeout_ms;
}
