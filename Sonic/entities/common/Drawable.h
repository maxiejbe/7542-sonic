#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <string>
//#include "../Renderer.h"
//#include "../Texture.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

class Drawable {
protected:
	virtual void draw(SDL_Rect camera) = 0;
};

#endif // !DRAWABLE_H

