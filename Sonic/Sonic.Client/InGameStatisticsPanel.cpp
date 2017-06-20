#include "InGameStatisticsPanel.h"

InGameStatisticsPanel::InGameStatisticsPanel(GameMode gameMode, int team)
{
	TTF_Init();
	fontLifes = TTF_OpenFont("fonts/SonicAdvance.ttf", 10);
	fontScore = TTF_OpenFont("fonts/SonicAdvance.ttf", 18);
	fontTestMode = TTF_OpenFont("fonts/SonicAdvance.ttf", 14);
	this->gameMode = gameMode;
	this->team = team;
}

InGameStatisticsPanel::~InGameStatisticsPanel()
{
}

void InGameStatisticsPanel::freeSurfaceStatistics()
{
	TTF_CloseFont(fontLifes);
	fontLifes = NULL;
	TTF_CloseFont(fontScore);
	fontScore = NULL;
	TTF_CloseFont(fontTestMode);
	fontTestMode = NULL;
}

void InGameStatisticsPanel::showStatistics(Player* player)
{
	// Check texture
	if (this->playerImage.getTexture() == nullptr && !this->playerImage.loadFromFile(PlayerUtils::getPlayerAvatarFilePath(player))) {
		LOG(logWARNING) << "No se pudo cargar la imagen del personaje '" << PlayerUtils::getPlayerAvatarFilePath(player) << "'.";
		return;
	}

	// Show Player image
	showPlayerImage(&playerImage, 30, 550);

	// Show userName
	string namePlayer = PlayerUtils::getPlayerName(player);
	showText(namePlayer, 80, 545, fontLifes, { 255, 255, 0 });

	// Show lifes
	string lifesPlayer = "X " + to_string(player->getLives());
	showText(lifesPlayer, 80, 570, fontLifes, { 255, 255, 255 });

	// Show score
	string score = "SCORE   " + to_string(player->getPoints());
	showText(score, 30, 10, fontScore, { 255, 255, 0 });

	// Show rings
	string rings = "RINGS   " + to_string(player->getRings());
	showText(rings, 30, 65, fontScore, { 255, 255, 0 });

	if (gameMode == GameMode::grupal) {
		// Show team
		string team = "TEAM " + to_string(this->team);
		showText(team, 720, 550, fontLifes, { 255, 255, 255 });

		// Show team score
		string teamScore = "TEAM SCORE   " + to_string(player->getTeamPoints());
		showText(teamScore, 515, 10, fontScore, { 255, 255, 255 });

		// Show team rings
		string teamRings = "TEAM RINGS   " + to_string(player->getTeamRings());
		showText(teamRings, 515, 65, fontScore, { 255, 255, 255 });
	}
	else if (gameMode == GameMode::colaborativo) {
		// Show grupal score
		string teamScore = "GRUPAL SCORE   " + to_string(player->getTeamPoints());
		showText(teamScore, 490, 10, fontScore, { 255, 255, 255 });

		// Show grupal rings
		string teamRings = "GRUPAL RINGS   " + to_string(player->getTeamRings());
		showText(teamRings, 490, 65, fontScore, { 255, 255, 255 });
	}

	// Show test mode
	if (player->getTestMode()) {
		showText("MODO DE PRUEBA ACTIVADO", 280, 550, fontTestMode, { 255, 0, 0 });
	}
}