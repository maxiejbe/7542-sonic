#ifndef WAITING_STATE_H
#define WAITING_STATE_H

#include "GameState.h"
#include "Banner.h"

class WaitingState : public GameState
{
public:
	void load(Game* game);
	int unload();
	void update(Game* game, float dt);
	void render(Game* game);

	static WaitingState* Instance() {
		return &m_WaitingState;
	}

protected:
	WaitingState() {}

private:
	static WaitingState m_WaitingState;
};

#endif // !WAITING_STATE_H

