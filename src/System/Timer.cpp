#include <Arduino.h>

#include "Timer.h"

Timer::Timer() : _timeout_ms(0), _nextTimeout(0) {
}

void Timer::setTimeout(const uint32_t timeout_ms) {
  _timeout_ms = timeout_ms;
}

uint32_t Timer::getTriggerTimeInSec() const {
  return (_nextTimeout - millis()) / 1000;
}

// cppcheck-suppress unusedFunction
bool Timer::isActive() const {
  return _nextTimeout != 0;
}

// cppcheck-suppress unusedFunction
void Timer::reset() {
  _nextTimeout = 0;
}

bool Timer::check() {
  return millis() > _nextTimeout;
}

void Timer::start() {
  _nextTimeout = millis() + _timeout_ms;
}
