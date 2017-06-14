#include "SelectTeamState.h"

SelectTeamState SelectTeamState::m_SelectTeamState;

void SelectTeamState::load(Game* game)
{
	TTF_Init();
	fontTeam = TTF_OpenFont("fonts/Retro_Stereo_Wide.ttf", 35);
	texture.loadFromFile("img/fiuba1.jpg");
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
	for (int i = 0; i < OPCMENU; i++) {
		if (menus[i] != NULL) {
			SDL_FreeSurface(menus[i]);
		}
	}

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
		for (int i = 0; i < OPCMENU; i++)
		{
			if (i != option) { team[i] = false; }
		}

		// Send selected team
		Message* clientResponse = new Message();
		clientResponse->setType(MessageType::player_assign_ok);
		clientResponse->setTeamId(selectedTeam);
		NetworkManager::getInstance().sendMessage(clientResponse);

		// Connect
		game->changeState(ConnectState::Instance());
	}
}

void SelectTeamState::render(Game* game)
{
	this->updateAndRenderOptions();
	this->renderSelectedOption();
}

void SelectTeamState::initColorNameOptions()
{
	option = 0;
	menus[option] = TTF_RenderText_Solid(fontTeam, labels[option], color[1]);

	for (int i = 0; i < OPCMENU; i++)
	{
		if (i != option)
		{
			selected[i] = false;
			menus[i] = TTF_RenderText_Solid(fontTeam, labels[i], color[0]);
		}
	}
}

void SelectTeamState::renderSelectedOption()
{
	selected[option] = true;
	for (int i = 0; i < OPCMENU; i++)
	{
		if (i != option) { selected[i] = false; }
	}

	for (int i = 0; i < OPCMENU; i++)
	{
		if (selected[i] == true) { menus[i] = TTF_RenderText_Solid(fontTeam, labels[i], color[1]); }
		else if (team[i] == true) { menus[i] = TTF_RenderText_Solid(fontTeam, labels[i], color[2]); }
		else { menus[i] = TTF_RenderText_Solid(fontTeam, labels[i], color[0]); }
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
	SDL_Rect Message_rect;
	SDL_Texture* text;

	//Show team1 text
	text = SDL_CreateTextureFromSurface(Renderer::getInstance().gRenderer, menus[0]);
	Message_rect.x = 190;
	Message_rect.y = 410;
	Message_rect.w = menus[0]->w;
	Message_rect.h = menus[0]->h;
	SDL_RenderCopy(Renderer::getInstance().gRenderer, text, NULL, &Message_rect);

	//Show team2 text
	text = SDL_CreateTextureFromSurface(Renderer::getInstance().gRenderer, menus[1]);
	Message_rect.x = 490;
	Message_rect.y = 410;
	Message_rect.w = menus[1]->w;
	Message_rect.h = menus[1]->h;
	SDL_RenderCopy(Renderer::getInstance().gRenderer, text, NULL, &Message_rect);


	SDL_RenderPresent(Renderer::getInstance().gRenderer);
}

void SelectTeamState::showBackgroundImage()
{
	SDL_Rect dstrect;
	dstrect = { 0, 0, SDLWindow::getInstance().getScreenWidth(), SDLWindow::getInstance().getScreenHeight() };
	SDL_RenderCopy(Renderer::getInstance().gRenderer, backgroundTexture.getTexture(), NULL, &dstrect);
}