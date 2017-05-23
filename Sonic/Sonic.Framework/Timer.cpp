#include "Timer.h"

void Timer::reset() { 
	beg_ = clock_::now(); 
}

double Timer::elapsed() const {
	return duration_cast<millisecond_>(clock_::now() - beg_).count();
}