#ifndef RENDERER_H
#define RENDERER_H

#include "SDLWindow.h"
#include "Logger.h"

class Renderer {
public:
	static Renderer& getInstance() {
		static Renderer instance;
		return instance;
	}
	bool Create();
	void Close();
	SDL_Renderer* gRenderer = NULL;
private:
	Renderer() {}
public:
	Renderer(Renderer const&) = delete;
	void operator=(Renderer const&) = delete;
};


#endif // !RENDERER_H
