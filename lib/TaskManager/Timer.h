#ifndef TIMER_H_
#define TIMER_H_

#include <TimeLib.h>

class Timer
{
public:
	Timer();

	void setTimeout(const time_t timeout_sec);
	time_t getTriggerTime() const;

	bool isActive() const;

	void reset();

	bool check();
	void start();

private:
	time_t _timeout_sec;
	time_t _timeout;
};

#endif
