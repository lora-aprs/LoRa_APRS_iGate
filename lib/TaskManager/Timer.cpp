#include "Timer.h"

Timer::Timer()
	: _timeout_sec(0), _timeout(0)
{
}

void Timer::setTimeout(const time_t timeout_sec)
{
	_timeout_sec = timeout_sec;
}

time_t Timer::getTriggerTime() const
{
	return _timeout;
}

bool Timer::isActive() const
{
	return _timeout != 0;
}

void Timer::reset()
{
	_timeout = 0;
}

bool Timer::check()
{
	return now() > _timeout;
}

void Timer::start()
{
	_timeout = now() + _timeout_sec;
}
