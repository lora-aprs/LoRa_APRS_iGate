#ifndef TIMER_H_
#define TIMER_H_

#include <TimeLib.h>

class Timer {
public:
  Timer();

  void   setTimeout(const uint32_t timeout_ms);
  time_t getTriggerTimeInSec() const;

  bool isActive() const;

  void reset();

  bool check();
  void start();

private:
  uint32_t _timeout_ms;
  uint32_t _nextTimeout;
};

#endif
