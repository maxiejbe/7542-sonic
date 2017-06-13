#ifndef DRAWABLE_H
#define DRAWABLE_H

//#include <string>
//#include <SDL.h>
//#include <SDL2_gfxPrimitives.h>
//#include <algorithm>

class Drawable {
public:
	virtual void draw(int camX, int camY) = 0;
};

#endif // !DRAWABLE_H

