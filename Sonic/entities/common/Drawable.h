#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <string>
//#include "../Renderer.h"
//#include "../Texture.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <algorithm>

class Drawable {
public:
	virtual void draw(SDL_Rect camera) = 0;
};

#endif // !DRAWABLE_H

