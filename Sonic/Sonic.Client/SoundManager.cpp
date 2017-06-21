#include "SoundManager.h"

bool SoundManager::create()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		LOG(logERROR) << "SDL_mixer no pudo ser inicializado! SDL_mixer Error: " << Mix_GetError();
		return false;
	}
	return true;
}

void SoundManager::playMusic(const string & fileName)
{
	if (Mix_PlayingMusic() == 0) {
		music = Mix_LoadMUS(fileName.c_str());
		if (music == NULL) {
			LOG(logERROR) << "Error al cargar la música! SDL_mixer Error: " << Mix_GetError();
			return;
		}
		Mix_PlayMusic(music, -1);
	}
}

void SoundManager::playSound(const string & fileName)
{
	sound = Mix_LoadWAV(fileName.c_str());
	if (sound == NULL) {
		LOG(logERROR) << "Error al cargar el sonido! SDL_mixer Error: " << Mix_GetError();
		return;
	}
	Mix_PlayChannel(-1, sound, 0);
}

void SoundManager::pauseMusic()
{
	if (Mix_PlayingMusic() == 1) {
		Mix_PauseMusic();
	}
}

void SoundManager::unpauseMusic()
{
	if (Mix_PausedMusic() == 1) {
		Mix_ResumeMusic();
	}
}


void SoundManager::stopMusic()
{
	Mix_HaltMusic();
}

void SoundManager::close()
{
	Mix_FreeChunk(sound);
	sound = NULL;
	Mix_FreeMusic(music);
	music = NULL;
}