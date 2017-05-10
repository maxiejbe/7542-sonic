#include "Banner.h"

Banner::Banner(string text, SDL_Color color)
{
	TTF_Init();
	this->font = TTF_OpenFont("fonts/sega.ttf", 30);
	this->image.loadFromFile("img/sonic_orig.png");
	this->text = text;
	this->color = color;
}

Banner::~Banner()
{
	freeSurfaceBanner();
	TTF_CloseFont(font);
	font = NULL;
}

void Banner::freeSurfaceBanner()
{
	SDL_FreeSurface(message);
}

void Banner::showBanner()
{
	SDL_Event event;
	//string point = " ";
	//int i = 0;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			freeSurfaceBanner();
		}
	}

	//ShowLoadingPoints
	//point = point + ".";
	//i++;

	//Show Background
	boxRGBA(Renderer::getInstance().gRenderer, 0, 0, SDLWindow::getInstance().getScreenWidth(), SDLWindow::getInstance().getScreenHeight(), this->color.r, this->color.g, this->color.b, 255);

	//Init and show text
	string allpoint = this->text;
	message = TTF_RenderText_Solid(font, allpoint.c_str(), { 0, 0, 0 });
	SDL_Rect destrect;
	SDL_Texture* text = SDL_CreateTextureFromSurface(Renderer::getInstance().gRenderer, message);
	destrect.x = SDLWindow::getInstance().getScreenWidth() / 2 - message->clip_rect.w / 2;
	destrect.y = (int)(SDLWindow::getInstance().getScreenHeight() - SDLWindow::getInstance().getScreenHeight() / 3.5) + (2 * (message->clip_rect.h));
	destrect.w = message->w;
	destrect.h = message->h;
	SDL_RenderCopy(Renderer::getInstance().gRenderer, text, NULL, &destrect);

	//Show img
	destrect.x = (int)(SDLWindow::getInstance().getScreenWidth() / 2 - image.getWidth());
	destrect.y = SDLWindow::getInstance().getScreenHeight() / 2 - image.getHeight();
	destrect.w = image.getWidth();
	destrect.h = image.getHeight();
	SDL_RenderCopy(Renderer::getInstance().gRenderer, image.getTexture(), NULL, &destrect);

	SDL_RenderPresent(Renderer::getInstance().gRenderer);

	//SDL_Delay(1000);
}