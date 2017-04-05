#pragma once
#include <string>
#include "../../StreamingTexture.h"
class CircleImageCropper
{
private:
	int radio;
	SDL_Texture * targetTexture;

	bool isInCircle(int cx, int cy, int x, int y);
	bool initializeTargetTexture(int radio);
	void free();
	void drawPoint(int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
public:
	CircleImageCropper();
	~CircleImageCropper();
	bool crop(int radio, std::string imgPath);
	void render(int x, int y);
};

