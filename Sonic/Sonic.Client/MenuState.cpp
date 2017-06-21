#include "Game.h"
#include "MenuState.h"

MenuState MenuState::m_MenuState;

void MenuState::load(Game* game)
{
	TTF_Init();
	font = TTF_OpenFont("fonts/sega.ttf", 30);
	texture.loadFromFile("img/menu-background.jpg");

	selected[0] = true;
	selected[1] = false;

	color[0] = { 255,255,255 }; // White
	color[1] = { 255,0,0 }; // Red

	gameMode = NetworkManager::getInstance().getGameMode();

	connectionStatus = DISCONNECTED;

	labels[0] = "Connect";
	labels[1] = "Exit";

	initColorNameOptions();
	showBackgroundImage();
	SoundManager::getInstance().playMusic("sounds/menu.mp3");
}

int MenuState::unload()
{
	TTF_CloseFont(font);
	font = NULL;

	return 0;
}

void MenuState::update(Game* game, float dt)
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
			this->connectionStatus = CONNECTED;
			game->changeState(ConnectState::Instance());
		}
		else if (selected[1]) {
			game->quit();
		}
	}
}

void MenuState::render(Game* game)
{
	this->updateAndRenderOptions();
	this->renderSelectedOption();
}

void MenuState::initColorNameOptions()
{
	textureConnect.loadFromFont(font, labels[0], color[1]);
	textureExit.loadFromFont(font, labels[1], color[0]);
}

void MenuState::showBackgroundImage()
{
	SDL_Rect dstrect;
	dstrect = { 0, 0, SDLWindow::getInstance().getScreenWidth(), SDLWindow::getInstance().getScreenHeight() };
	SDL_RenderCopy(Renderer::getInstance().gRenderer, texture.getTexture(), NULL, &dstrect);
}

void MenuState::renderSelectedOption()
{
	if (option == 0) {
		selected[0] = true;
		selected[1] = false;
		textureConnect.loadFromFont(font, labels[0], color[1]);
		textureExit.loadFromFont(font, labels[1], color[0]);
	}
	else {
		selected[1] = true;
		selected[0] = false;
		textureExit.loadFromFont(font, labels[1], color[1]);
		textureConnect.loadFromFont(font, labels[0], color[0]);
	}
}

int MenuState::getNextOption(int option, int order) {
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

void MenuState::updateAndRenderOptions()
{
	int x = (SDLWindow::getInstance().getScreenWidth() / 2) - (151 / 2);
	int y = (int)(SDLWindow::getInstance().getScreenHeight() - SDLWindow::getInstance().getScreenHeight() / 4);

	textureConnect.render(x, y, NULL);

	x = SDLWindow::getInstance().getScreenWidth() / 2 - 81 / 2;
	y = (int)(SDLWindow::getInstance().getScreenHeight() - SDLWindow::getInstance().getScreenHeight() / 4) + (2 * (31));
	textureExit.render(x, y, NULL);

	SDL_RenderPresent(Renderer::getInstance().gRenderer);
}