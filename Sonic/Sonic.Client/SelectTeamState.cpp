#include "SelectTeamState.h"

SelectTeamState SelectTeamState::m_SelectTeamState;

void SelectTeamState::load(Game* game)
{
	TTF_Init();
	fontTeam = TTF_OpenFont("fonts/Retro_Stereo_Wide.ttf", 35);
	backgroundTexture.loadFromFile("img/teams-background.jpg");

	selected[0] = true;
	selected[1] = false;

	team[0] = team[1] = false;

	color[0] = { 255,255,255 }; //Blanco
	color[1] = { 255,0,0 }; //Rojo
	color[2] = { 255,255,0 }; //Amarillo

	labels[0] = "TEAM 1";
	labels[1] = "TEAM 2";

	initColorNameOptions();
	showBackgroundImage();
}

int SelectTeamState::unload()
{
	TTF_CloseFont(fontTeam);
	fontTeam = NULL;

	return 0;
}

void SelectTeamState::update(Game* game, float dt)
{
	InputManager* input = InputManager::getInstance();
	input->update();

	if (input->quitRequested()) {
		game->quit();
		return;
	}

	if (input->isKeyDown(KEY_LEFT)) {
		option = this->getNextOption(option, -1);
	}

	if (input->isKeyDown(KEY_RIGHT)) {
		option = this->getNextOption(option, 1);
	}

	if (input->isKeyDown(KEY_RETURN)) {
		team[option] = true;
		selectedTeam = option + 1;
		for (int i = 0; i < OPCMENU; i++) {
			if (i != option) {
				team[i] = false;
			}
		}

		// Send selected team
		Message* clientResponse = new Message();
		clientResponse->setType(MessageType::player_assign_ok);
		clientResponse->setTeamId(selectedTeam);
		NetworkManager::getInstance().sendMessage(clientResponse);

		game->changeState(PlayState::Instance(selectedTeam));
	}
}

void SelectTeamState::render(Game* game)
{
	this->updateAndRenderOptions();
	this->renderSelectedOption();
}

int SelectTeamState::getTeam()
{
	return this->selectedTeam;
}

void SelectTeamState::initColorNameOptions()
{
	option = 0;
	textures[option].loadFromFont(fontTeam, labels[option], color[1]);

	for (int i = 0; i < OPCMENU; i++) {
		if (i != option) {
			selected[i] = false;
			textures[i].loadFromFont(fontTeam, labels[i], color[0]);
		}
	}
}

void SelectTeamState::renderSelectedOption()
{
	selected[option] = true;
	for (int i = 0; i < OPCMENU; i++) {
		if (i != option) {
			selected[i] = false;
		}
	}

	for (int i = 0; i < OPCMENU; i++) {
		if (selected[i] == true) {
			textures[i].loadFromFont(fontTeam, labels[i], color[1]);
		}
		else if (team[i] == true) {
			textures[i].loadFromFont(fontTeam, labels[i], color[2]);
		}
		else {
			textures[i].loadFromFont(fontTeam, labels[i], color[0]);
		}
	}
}

int SelectTeamState::getNextOption(int option, int order) {
	if (order > 0) {
		for (int i = option + 1; i < OPCMENU; i++) {
			return i;
		}
	}
	else if (order < 0) {
		for (int i = option - 1; i >= 0; i--) {
			return i;
		}
	}
	return option;
}

void SelectTeamState::updateAndRenderOptions()
{
	int x = 190;
	int y = 460;
	for (int i = 0; i < OPCMENU; i++) {
		textures[i].render(x, y, NULL);
		x += 300;
	}

	SDL_RenderPresent(Renderer::getInstance().gRenderer);
}

void SelectTeamState::showBackgroundImage()
{
	SDL_Rect dstrect;
	dstrect = { 0, 0, SDLWindow::getInstance().getScreenWidth(), SDLWindow::getInstance().getScreenHeight() };
	SDL_RenderCopy(Renderer::getInstance().gRenderer, backgroundTexture.getTexture(), NULL, &dstrect);
}