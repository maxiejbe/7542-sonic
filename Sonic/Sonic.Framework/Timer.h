#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>

using namespace std::chrono;

class Timer
{
public:
	Timer() : beg_(clock_::now()) {}
	void reset();
	double elapsed() const;

private:
	typedef high_resolution_clock clock_;
	typedef duration<int, std::milli> millisecond_;
	time_point<clock_> beg_;
};

#endif // !TIMER_H