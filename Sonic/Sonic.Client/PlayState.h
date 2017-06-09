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
#include "Timer.h"
#include <stdio.h>
#include <string>
#include <cmath>
#include <unordered_map>

class PlayState : public GameState {
public:
	void load(Game* game);
	int unload();
	void update(Game* game, float dt);
	void render(Game* game);

	static PlayState* Instance() {
		return &m_PlayState;
	}

protected:
	PlayState() {}

private:
	static PlayState m_PlayState;

	bool clientNumberSet();

	Scenario scenario;
	Camera* cameraModel;
	vector<EntityView*> entityViews;

	SDL_Rect camera;
	vector<LayerView> layerViews;
	InGameStatisticsPanel statisticsPanel;

	int scenarioWidth;
	int scenarioHeight;

	int playerNumber = -1;
	string configPath;

	Timer stepTimer;
	Message* lastMessage;
	bool lastMessageFlag;
};

#endif // !PLAY_STATE_H
