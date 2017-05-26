#ifndef CONNECT_STATE_H
#define CONNECT_STATE_H

#include "GameState.h"

class ConnectState : public GameState {
public:
	void load(Game* game);
	int unload();
	void update(Game* game, float dt);
	void render(Game* game);

	static ConnectState* Instance() {
		return &m_ConnectState;
	}

protected:
	ConnectState() {}

private:
	static ConnectState m_ConnectState;

	void reconnect(Game* game);

	ServerConfiguration serverConfig;
	bool connected;
};


#endif // !CONNECT_STATE_H

