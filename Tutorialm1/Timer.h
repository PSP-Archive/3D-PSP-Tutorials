#ifndef TIMER_H_
#define TIMER_H_

#include "time.h"

class Timer {

protected:
	time_t		TimeNow_;
	time_t		TimeStart_;
	bool		timerStarted_;

public:
	void startTimer();
	void resetTimer();
	int getTimer();

};

#endif
