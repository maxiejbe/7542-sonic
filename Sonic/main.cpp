#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "LTexture.cpp"
#include "LTimer.cpp"
#include "Dot.cpp"
#include "Logger.h"
#include "Parser.h"

//The dimensions of the level
const int LEVEL_WIDTH = 3328; // TODO: tomar del json
const int LEVEL_HEIGHT = 768; // TODO: tomar del json

//Screen dimension constants
const int SCREEN_WIDTH = 800; // TODO: tomar del json
const int SCREEN_HEIGHT = 600; // TODO: tomar del json

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gDotTexture;
LTexture gBGTexture;

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
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
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
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

// Dot

Dot::Dot()
{
	//Initialize the offsets
	mPosX = 0;
	mPosY = SCREEN_HEIGHT / 2;

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

// Timer

LTimer::LTimer()
{
	//Initialize the variables
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = false;
}

void LTimer::start()
{
	//Start the timer
	mStarted = true;

	//Unpause the timer
	mPaused = false;

	//Get the current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void LTimer::stop()
{
	//Stop the timer
	mStarted = false;

	//Unpause the timer
	mPaused = false;

	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void LTimer::pause()
{
	//If the timer is running and isn't already paused
	if (mStarted && !mPaused)
	{
		//Pause the timer
		mPaused = true;

		//Calculate the paused ticks
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void LTimer::unpause()
{
	//If the timer is running and paused
	if (mStarted && mPaused)
	{
		//Unpause the timer
		mPaused = false;

		//Reset the starting ticks
		mStartTicks = SDL_GetTicks() - mPausedTicks;

		//Reset the paused ticks
		mPausedTicks = 0;
	}
}

Uint32 LTimer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (mStarted)
	{
		//If the timer is paused
		if (mPaused)
		{
			//Return the number of ticks when the timer was paused
			time = mPausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - mStartTicks;
		}
	}

	return time;
}

bool LTimer::isStarted()
{
	//Timer is running and paused or unpaused
	return mStarted;
}

bool LTimer::isPaused()
{
	//Timer is running and paused
	return mPaused && mStarted;
}


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
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
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

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
	

	//TODO: Take params from argv
	Parser* p = new Parser("config/params.json");

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Dot dot;

			//Keeps track of time between steps
			LTimer stepTimer;

			//The camera area
			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

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
				camera.x = ((int)dot.getPosX() + Dot::DOT_WIDTH / 2) - SCREEN_WIDTH / 2;
				camera.y = ((int)dot.getPosY() + Dot::DOT_HEIGHT / 2) - SCREEN_HEIGHT / 2;

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
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render background
				gBGTexture.render(0, 0, &camera);

				//Render objects
				dot.render(camera.x, camera.y);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}