#include "Banner.h"

Banner::Banner(string text, SDL_Color color, string imagePath)
{
	TTF_Init();
	this->font = TTF_OpenFont("fonts/sega.ttf", 30);
	this->image.loadFromFile(imagePath);
	this->text = text;
	this->color = color;
}

Banner::Banner(string text, SDL_Color color)
{
	TTF_Init();
	this->font = TTF_OpenFont("fonts/sega.ttf", 30);
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
	SDL_Rect destrect;

	// Show image
	if (this->image.getTexture() != nullptr) {
		destrect.w = image.getWidth();
		destrect.h = image.getHeight();

		this->image.render(0, 0, &destrect);
	}

	// Show Background
	boxRGBA(Renderer::getInstance().gRenderer, 0, 0, SDLWindow::getInstance().getScreenWidth(), SDLWindow::getInstance().getScreenHeight(), this->color.r, this->color.g, this->color.b, this->color.a);

	// Init and show text
	string allpoint = this->text;

	textTexture.loadFromFont(font, allpoint, { 255, 255, 255 });

	int x = SDLWindow::getInstance().getScreenWidth() / 2 - textTexture.getWidth() / 2;
	int y = (int)(SDLWindow::getInstance().getScreenHeight() - SDLWindow::getInstance().getScreenHeight() / 3.5) + (3 * (textTexture.getHeight()));

	textTexture.render(x, y, NULL);

	/*message = TTF_RenderText_Solid(font, allpoint.c_str(), { 255, 255, 255 });

	SDL_Texture* text = SDL_CreateTextureFromSurface(Renderer::getInstance().gRenderer, message);
	destrect.x = SDLWindow::getInstance().getScreenWidth() / 2 - message->clip_rect.w / 2;
	destrect.y = (int)(SDLWindow::getInstance().getScreenHeight() - SDLWindow::getInstance().getScreenHeight() / 3.5) + (3 * (message->clip_rect.h));
	destrect.w = message->w;
	destrect.h = message->h;
	SDL_RenderCopy(Renderer::getInstance().gRenderer, text, NULL, &destrect);*/

	SDL_RenderPresent(Renderer::getInstance().gRenderer);
}