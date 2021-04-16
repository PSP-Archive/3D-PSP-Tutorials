#include "Timer.h"
#include <psputils.h>

void Timer::startTimer() {
	
	// getting current time
	sceKernelLibcTime(&this->TimeStart_);
	
	// set bool timer is started
	this->timerStarted_ = true;
}


int Timer::getTimer() {
	if(!this->timerStarted_)
		return 0;

	// getting current time
	sceKernelLibcTime(&this->TimeNow_);

	// return the time now minus the start time, resulting in difference time.
	return ((int)this->TimeNow_ - (int)this->TimeStart_);

}

void Timer::resetTimer() {
	this->timerStarted_ = false;

}

