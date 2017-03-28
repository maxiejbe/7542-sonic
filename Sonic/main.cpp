#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "LTexture.h"
#include "Timer.h"
#include "Dot.h"
#include "Logger.h"
#include "Parser.h"
#include "Entities/Window.h"
#include "Renderer.h"

//The dimensions of the level
const int LEVEL_WIDTH = 3328; // TODO: tomar del json
const int LEVEL_HEIGHT = 768; // TODO: tomar del json

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Scene textures 
LTexture gDotTexture;
LTexture gBGTexture;

// TODO: moverlo a LTexture.cpp

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(Renderer::getInstance().gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(Renderer::getInstance().gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

// TODO: moverlo a Dot.cpp

Dot::Dot()
{
	//Initialize the offsets
	mPosX = 0;
	mPosY = SDLWindow::getInstance().SCREEN_HEIGHT / 2;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

void Dot::handleEvent(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY -= DOT_VEL; break;
		case SDLK_DOWN: mVelY += DOT_VEL; break;
		case SDLK_LEFT: mVelX -= DOT_VEL; break;
		case SDLK_RIGHT: mVelX += DOT_VEL; break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY += DOT_VEL; break;
		case SDLK_DOWN: mVelY -= DOT_VEL; break;
		case SDLK_LEFT: mVelX += DOT_VEL; break;
		case SDLK_RIGHT: mVelX -= DOT_VEL; break;
		}
	}
}

void Dot::move(float timeStep)
{
	//Move the dot left or right
	mPosX += mVelX * timeStep;

	//If the dot went too far to the left or right
	if (mPosX < 0)
	{
		mPosX = 0;
	}
	else if (mPosX > LEVEL_WIDTH - DOT_WIDTH)
	{
		mPosX = LEVEL_WIDTH - DOT_WIDTH;
	}

	//Move the dot up or down
	mPosY += mVelY * timeStep;

	//If the dot went too far up or down
	if (mPosY < 0)
	{
		mPosY = 0;
	}
	else if (mPosY > LEVEL_HEIGHT - DOT_HEIGHT)
	{
		mPosY = LEVEL_HEIGHT - DOT_HEIGHT;
	}
}

void Dot::render(int camX, int camY)
{
	//Show the dot relative to the camera
	gDotTexture.render((int)(mPosX - camX), (int)(mPosY - camY));
}

float Dot::getPosX()
{
	return mPosX;
}

float Dot::getPosY()
{
	return mPosY;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if (!gDotTexture.loadFromFile("img/dot.bmp"))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	//Load background texture
	if (!gBGTexture.loadFromFile("img/level.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	gDotTexture.free();
	gBGTexture.free();

	//Destroy window
	SDLWindow::getInstance().Close();

	// Destroy renderer
	Renderer::getInstance().Close();

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	/* Ejemplo de uso de Logger

	Logger::Init();
	Logger::LoggingLevel() = Logger::FromString("low"); // TODO: tomar de json

	LOG(logINFO) << "Informacion bla bla bla.";
	LOG(logWARNING) << "Cuidado, es un warning!";
	LOG(logERROR) << "Este es un error de ejemplo.";
	*/

	// TODO: tomar de json
	SDLWindow::getInstance().SCREEN_WIDTH = 800;
	SDLWindow::getInstance().SCREEN_HEIGHT = 600;

	//TODO: Take params from argv
	Parser* p = new Parser("config/params.json");
	Window window;
	p->Parse(&window);

	Configuration config;
	p->Parse(&config);

	Scenario scenario;
	p->Parse(&scenario);


	//Configuration config = p->ParseConfiguration();
	//Scenario scenario;
	//p->ParseScenario(&scenario);

	//Start up SDL and create window
	if (!SDLWindow::getInstance().Create() || !Renderer::getInstance().Create()) {
		printf("Failed to initialize!\n");
	}
	else {
		//Load media
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		}
		else {
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Dot dot;

			//Keeps track of time between steps
			Timer stepTimer;

			//The camera area
			SDL_Rect camera = { 0, 0, SDLWindow::getInstance().SCREEN_WIDTH, SDLWindow::getInstance().SCREEN_HEIGHT };

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					//Handle input for the dot
					dot.handleEvent(e);
				}

				//Calculate time step
				float timeStep = stepTimer.getTicks() / 1000.f;

				//Move for time step
				dot.move(timeStep);

				//Restart step timer
				stepTimer.start();

				//Center the camera over the dot
				camera.x = ((int)dot.getPosX() + Dot::DOT_WIDTH / 2) - SDLWindow::getInstance().SCREEN_WIDTH / 2;
				camera.y = ((int)dot.getPosY() + Dot::DOT_HEIGHT / 2) - SDLWindow::getInstance().SCREEN_HEIGHT / 2;

				//Keep the camera in bounds
				if (camera.x < 0)
				{
					camera.x = 0;
				}
				if (camera.y < 0)
				{
					camera.y = 0;
				}
				if (camera.x > LEVEL_WIDTH - camera.w)
				{
					camera.x = LEVEL_WIDTH - camera.w;
				}
				if (camera.y > LEVEL_HEIGHT - camera.h)
				{
					camera.y = LEVEL_HEIGHT - camera.h;
				}

				//Clear screen
				SDL_SetRenderDrawColor(Renderer::getInstance().gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(Renderer::getInstance().gRenderer);

				//Render background
				gBGTexture.render(0, 0, &camera);

				//Render objects
				dot.render(camera.x, camera.y);

				//Update screen
				SDL_RenderPresent(Renderer::getInstance().gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}