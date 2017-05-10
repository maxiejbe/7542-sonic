#include "Banner.h"

Banner::Banner()
{
	TTF_Init();
	font = TTF_OpenFont("fonts/sega.ttf", 30);
	image.loadFromFile("img/sonic_orig.png");
}


Banner::~Banner()
{
}

void Banner::freeSurfaceBanner()
{
	SDL_FreeSurface(message);
}

void Banner::showBanner() 
{
	bool isRunning = true;
	string point = " ";
	int i = 0;


	//ShowLoadingPoints
	i++;
	if (i == 10) 
	{ 
		point = " "; 
		i = 0;
	}
	else 
	{ 
		point = point + "."; 
	}
		
	//Show Background
	boxRGBA(Renderer::getInstance().gRenderer, 0, 0, SDLWindow::getInstance().getScreenWidth(), SDLWindow::getInstance().getScreenHeight(), 255, 0, 0, 255);

	//Init and show text
	color = { 255,255,255 };
	string allpoint = "Reconnecting" + point;
	message = TTF_RenderText_Solid(font, allpoint.c_str(), color);
	SDL_Rect destrect;
	SDL_Texture* text = SDL_CreateTextureFromSurface(Renderer::getInstance().gRenderer, message);
	destrect.x = SDLWindow::getInstance().getScreenWidth() / 2 - message->clip_rect.w / 2;
	destrect.y = (int)(SDLWindow::getInstance().getScreenHeight() - SDLWindow::getInstance().getScreenHeight() / 3.5) + (2 * (message->clip_rect.h));
	destrect.w = message->w;
	destrect.h = message->h;
	SDL_RenderCopy(Renderer::getInstance().gRenderer, text, NULL, &destrect);

	//Show img
	destrect.x = (int)(SDLWindow::getInstance().getScreenWidth() / 2 - image.getWidth()* 1.3);
	destrect.y = SDLWindow::getInstance().getScreenHeight() / 2 - image.getHeight();
	destrect.w = image.getWidth() * 2;
	destrect.h = image.getHeight() * 2;
	SDL_RenderCopy(Renderer::getInstance().gRenderer, image.getTexture(), NULL, &destrect);

	SDL_RenderPresent(Renderer::getInstance().gRenderer);

	SDL_Delay(1000);

}