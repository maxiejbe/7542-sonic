#pragma once
#include "Texture.h"
class StreamingTexture : public Texture
{
private:
	void *pixels;
	int pitch;
public:
	StreamingTexture();
	~StreamingTexture();

	bool lockTexture();
	bool unlockTexture();
	void* getPixels();
	int getPitch();
	void setBlendMode(SDL_BlendMode blending);

	virtual bool loadFromFile(std::string path);
};

