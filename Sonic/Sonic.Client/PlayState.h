#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "GameState.h"
#include "network/NetworkManager.h"
#include "Banner.h"
#include "Parser.h"
#include "entities/Layer.h"
#include "entities/Entity.h"
#include "entities/Scenario.h"
#include "views/LayerView.h"
#include "views/EntityView.h"
#include "views/common/EntityViewResolver.h"
#include "InGameStatisticsPanel.h"
#include "EndLevelState.h"
#include "GameOverState.h"
#include "Timer.h"
#include <stdio.h>
#include <string>
#include <cmath>
#include <unordered_map>

class PlayState : public GameState {
public:
	void load(Game* game);
	void loadSounds();
	int unload();
	void update(Game* game, float dt);
	void render(Game* game);

	static PlayState* Instance() {
		return &m_PlayState;
	}

	static PlayState* Instance(int team) {
		static PlayState m_PlayState(team);
		return &m_PlayState;
	}

protected:
	PlayState() {}
	PlayState(int team) { this->team = team; }

private:
	static PlayState m_PlayState;

	bool clientNumberSet();
	void showLevelBackgroundName(int level);

	Scenario scenario;
	Camera* cameraModel;

	SDL_Rect camera;
	vector<LayerView> layerViews;
	InGameStatisticsPanel* statisticsPanel;

	int scenarioWidth;
	int scenarioHeight;

	int playerNumber = -1;
	string configPath;

	Timer stepTimer;
	Message* lastMessage;
	bool lastMessageFlag;

	Player* ownPlayer;

	int team;

	Mix_Music* musicSound;
	Mix_Chunk* jumpSound;
	Mix_Chunk* ringSound;
};

#endif // !PLAY_STATE_H
