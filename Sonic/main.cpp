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
#include "Entities/Rectangle.h"
#include "entities/Circle.h"
#include "entities/Square.h"

//The dimensions of the level
const int LEVEL_WIDTH = 3328; // TODO: tomar del json
const int LEVEL_HEIGHT = 768; // TODO: tomar del json

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Scene textures 
LTexture gDotTexture;
//LTexture gBGTexture;
Layer gBGLayer;
LTexture gSpriteTexture;
LTexture gSpriteTexture1;

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

	//Load background Layer
	success = gBGLayer.loadLayer();

	//Load sprite texture
	if (!gSpriteTexture.loadFromFile("img/sprite.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}

	//Load sprite texture
	if (!gSpriteTexture1.loadFromFile("img/sprite.png"))
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
	gBGLayer.destroyLayer();
	gSpriteTexture.free();

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
				gBGLayer.renderLayer(0, 0, &camera);


				//Crop img = rect
				Rectangle rectangle = Rectangle(100, 100, 100, 100);
				rectangle.draw(camera);
				int x1 = 100 - camera.x;
				int y1 = 100 - camera.y;
				SDL_Rect dstrect = { x1, y1, 100, 100 };			
				SDL_Rect croprect = { 0, 0, 100, 100 };				
				SDL_RenderCopy(Renderer::getInstance().gRenderer, gSpriteTexture.getTexture(), &croprect, &dstrect);

				//Crop img < rect
				Rectangle rectangle1 = Rectangle(300, 300, 300, 300);
				rectangle1.draw(camera);
				x1 = 300 - camera.x;
				y1 = 300 - camera.y;
				SDL_Rect dstrect1 = { x1, y1, 200, 200 };
				SDL_Rect croprect1 = { 0, 0, 200, 200 };
				SDL_RenderCopy(Renderer::getInstance().gRenderer, gSpriteTexture1.getTexture(), &croprect1, &dstrect1);

				//Crop img > rect (img.h es mas chica que el rect.h)
				Rectangle rectangle2 = Rectangle(700, 200, 300, 100);
				rectangle2.draw(camera);
				x1 = 700 - camera.x;
				y1 = 200 - camera.y;
				SDL_Rect dstrect2 = { x1, y1, 200, 100 };
				SDL_Rect croprect2 = { 0, 0, 200, 100 }; //rect.w mas grande que img.w, queda la img.w
				SDL_RenderCopy(Renderer::getInstance().gRenderer, gSpriteTexture1.getTexture(), &croprect2, &dstrect2);

				//Crop img > rect (img.w es mas chica que el rect.w)
				Rectangle rectangle3 = Rectangle(1200, 50, 60, 400);
				rectangle3.draw(camera);
				x1 = 1200 - camera.x;
				y1 = 50 - camera.y;
				SDL_Rect dstrect3 = { x1, y1, 60, 200 };
				SDL_Rect croprect3 = { 0, 0, 60, 200 }; //rect.w mas chico que img.w, queda la rect.w, rect.h es mas grande que img.h entocnes queda igual
				SDL_RenderCopy(Renderer::getInstance().gRenderer, gSpriteTexture1.getTexture(), &croprect3, &dstrect3);



				Circle circle = Circle(1500,200, 100);
				circle.draw(camera);

				Square square = Square(1300, 300, 80);
				square.draw(camera);
				
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