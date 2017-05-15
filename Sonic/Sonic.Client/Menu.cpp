#include "Menu.h"

Menu::Menu()
{
	initMenu();
}

Menu::~Menu()
{
	freeSurfaceMenus();
}

void Menu::initMenu()
{
	TTF_Init();
	font = TTF_OpenFont("fonts/sega.ttf", 30);
	texture.loadFromFile("img/menu-background.jpg");

	selected[0] = true;
	selected[1] = selected[2] = false;

	color[0] = { 255,255,255 };
	color[1] = { 255,0,0 };
	color[2] = { 192,192,192 };

	connectionStatus = DISCONNECTED;
}

void Menu::initColorNameOptions()
{
	option = 0;
	menus[option] = TTF_RenderText_Solid(font, labels[option], color[1]);

	for (int i = 0; i < OPCMENU; i++)
	{
		if (i != option)
		{
			selected[i] = false;
			if (this->connectionStatus == DISCONNECTED && labels[i] == "Disconnect") { menus[i] = TTF_RenderText_Solid(font, labels[i], color[2]); }
			else { menus[i] = TTF_RenderText_Solid(font, labels[i], color[0]); }
		}
	}
}

void Menu::showBackgroundImage()
{
	SDL_Rect dstrect;
	dstrect = { 0, 0, SDLWindow::getInstance().getScreenWidth(), SDLWindow::getInstance().getScreenHeight() };
	SDL_RenderCopy(Renderer::getInstance().gRenderer, texture.getTexture(), NULL, &dstrect);
}

void Menu::updateAndRenderOptions()
{
	SDL_Rect Message_rect;
	for (int i = 0; i < OPCMENU; i += 1)
	{
		SDL_Texture* text = SDL_CreateTextureFromSurface(Renderer::getInstance().gRenderer, menus[i]);
		Message_rect.x = SDLWindow::getInstance().getScreenWidth() / 2 - menus[i]->clip_rect.w / 2;
		Message_rect.y = (int)(SDLWindow::getInstance().getScreenHeight() - SDLWindow::getInstance().getScreenHeight() / 3.5) + (2 * (menus[i]->clip_rect.h) * i);
		Message_rect.w = menus[i]->w;
		Message_rect.h = menus[i]->h;
		SDL_RenderCopy(Renderer::getInstance().gRenderer, text, NULL, &Message_rect);
	}

	SDL_RenderPresent(Renderer::getInstance().gRenderer);
}

void Menu::freeSurfaceMenus()
{
	for (int i = 0; i < OPCMENU; i++) {
		if (menus[i] != NULL) {
			SDL_FreeSurface(menus[i]);
		}
	}
}

void Menu::changeSelectedOption()
{
	selected[option] = true;
	menus[option] = TTF_RenderText_Solid(font, labels[option], color[1]);

	for (int i = 0; i < OPCMENU; i++)
	{
		if (i != option)
		{
			selected[i] = false;
			if (this->connectionStatus == DISCONNECTED && labels[i] == "Disconnect") { menus[i] = TTF_RenderText_Solid(font, labels[i], color[2]); }
			else { menus[i] = TTF_RenderText_Solid(font, labels[i], color[0]); }
		}
	}
}

int Menu::showMenu()
{
	labels[0] = this->connectionStatus == DISCONNECTED ? "Connect" : "Resume";
	labels[1] = "Disconnect";
	labels[2] = "Exit";

	initColorNameOptions();
	showBackgroundImage();
	updateAndRenderOptions();

	bool isRunning = true;

	while (isRunning)
	{
		InputManager* input = InputManager::getInstance();
		input->update();

		if (input->quitRequested()) {
			return 2;
		}

		if (input->isKeyDown(KEY_UP)) {
			setEnabledOptions();
			option = this->getNextOption(option, -1);
			changeSelectedOption();
			updateAndRenderOptions();
		}
		if (input->isKeyDown(KEY_DOWN)) {
			setEnabledOptions();
			option = this->getNextOption(option, 1);
			changeSelectedOption();
			updateAndRenderOptions();
		}
		if (input->isKeyDown(KEY_RETURN)) {
			if (selected[0]) {
				// Connect
				this->connectionStatus = CONNECTED;
				return 0;
			}
			else if (selected[1]) {
				// Disconnect
				this->connectionStatus = DISCONNECTED;
				return 1;
			}
			else if (selected[2]) {
				// Exit
				return 2;
			}
		}
		if (input->isKeyDown(KEY_ESCAPE)) {
			return 0;
		}
	}
	return 0;
}

int Menu::getNextOption(int option, int order) {
	if (order > 0) {
		// Abajo
		for (int i = option + 1; i < OPCMENU; i++) {
			if (enabled[i]) {
				return i;
			}
		}
	}
	else if (order < 0) {
		// Arriba
		for (int i = option - 1; i >= 0; i--) {
			if (enabled[i]) {
				return i;
			}
		}
	}
	return option;
}

void Menu::setEnabledOptions()
{
	for (int i = 0; i < OPCMENU; i++) {
		enabled[i] = (this->connectionStatus == DISCONNECTED && labels[i] == "Disconnect") ?
			false : true;
	}
}