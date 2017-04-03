#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class Timer
{
public:
	Timer();

	void start();
	void stop();
	void pause();
	void unpause();
	Uint32 getTicks();

	bool isStarted();
	bool isPaused();
private:
	Uint32 startTicks;
	Uint32 pausedTicks;

	bool paused;
	bool started;
};