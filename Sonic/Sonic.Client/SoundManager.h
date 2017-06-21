#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include "Logger.h"

using namespace std;

class SoundManager {
public:
	static SoundManager& getInstance() {
		static SoundManager instance;
		return instance;
	}

	bool create();
	void close();
	void playMusic(const string& fileName);
	//void pauseMusic();
	//void stopMusic();
	void playSound(const string& fileName);

	//bool isPaused();
	//bool isStopped();
	//bool isPlaying();

	SoundManager(SoundManager const&) = delete;
	void operator=(SoundManager const&) = delete;
private:
	SoundManager() {}

	Mix_Music* music;
	Mix_Chunk* sound;
};

#endif // !SOUNDMANAGER_H
