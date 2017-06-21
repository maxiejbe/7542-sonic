#include "Game.h"
#include "PauseState.h"
#include "MenuState.h"

PauseState PauseState::m_PauseState;

void PauseState::load(Game* game)
{
	TTF_Init();
	font = TTF_OpenFont("fonts/sega.ttf", 30);
	texture.loadFromFile("img/menu-background.jpg");

	selected[0] = true;
	selected[1] = selected[2] = false;

	color[0] = { 255,255,255 }; // White
	color[1] = { 255,0,0 }; // Red

	labels[0] = "Resume";
	labels[1] = "Disconnect";
	labels[2] = "Exit";

	initColorNameOptions();
	showBackgroundImage();
}

int PauseState::unload()
{
	TTF_CloseFont(font);
	font = NULL;

	return 0;
}

void PauseState::update(Game* game, float dt)
{
	InputManager* input = InputManager::getInstance();
	input->update();

	if (input->quitRequested()) {
		game->quit();
		return;
	}

	if (input->isKeyDown(KEY_UP)) {
		option = this->getNextOption(option, -1);
	}

	if (input->isKeyDown(KEY_DOWN)) {
		option = this->getNextOption(option, 1);
	}

	if (input->isKeyDown(KEY_RETURN)) {
		if (selected[0]) {
			// Resume
			game->popState();
		}
		else if (selected[1]) {
			// Disconnect
			NetworkManager::getInstance().disconnect();
			game->changeState(MenuState::Instance());
		}
		else if (selected[2]) {
			// Exit
			game->quit();
		}
	}
}

void PauseState::render(Game* game)
{
	this->updateAndRenderOptions();
	this->renderSelectedOption();
}

void PauseState::initColorNameOptions()
{
	option = 0;
	textures[option].loadFromFont(font, labels[option], color[1]);

	for (int i = 0; i < OPCMENU; i++) {
		if (i != option) {
			selected[i] = false;
			textures[i].loadFromFont(font, labels[i], color[0]);
		}
	}
}

void PauseState::showBackgroundImage()
{
	SDL_Rect dstrect;
	dstrect = { 0, 0, SDLWindow::getInstance().getScreenWidth(), SDLWindow::getInstance().getScreenHeight() };
	SDL_RenderCopy(Renderer::getInstance().gRenderer, texture.getTexture(), NULL, &dstrect);
}

void PauseState::renderSelectedOption()
{
	selected[option] = true;
	textures[option].loadFromFont(font, labels[option], color[1]);

	for (int i = 0; i < OPCMENU; i++) {
		if (i != option) {
			selected[i] = false;
			textures[i].loadFromFont(font, labels[i], color[0]);
		}
	}
}

int PauseState::getNextOption(int option, int order) {
	if (order > 0) {
		// Abajo
		for (int i = option + 1; i < OPCMENU; i++) {
			return i;
		}
	}
	else if (order < 0) {
		// Arriba
		for (int i = option - 1; i >= 0; i--) {
			return i;
		}
	}
	return option;
}

void PauseState::updateAndRenderOptions()
{
	for (int i = 0; i < OPCMENU; i++) {
		int x = SDLWindow::getInstance().getScreenWidth() / 2 - textures[i].getWidth() / 2;
		int y = (int)(SDLWindow::getInstance().getScreenHeight() - SDLWindow::getInstance().getScreenHeight() / 3.5) + (2 * (textures[i].getHeight()) * i);
		textures[i].render(x, y, NULL);
	}

	SDL_RenderPresent(Renderer::getInstance().gRenderer);
}