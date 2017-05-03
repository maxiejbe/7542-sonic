#include "MultiplayerManager.h"
#include "MockPlayer.h"
#include <time.h>   

//Take a look at: http://stackoverflow.com/questions/16948064/unresolved-external-symbol-lnk2019
using namespace std;

void updatePlayer(MockPlayer * player, char option) {
	switch (option)
	{
	case 'w':
		player->setPosY(player->getPosY() + 1);
		break;
	case 'a':
		player->setPosX(player->getPosX() - 1);
		break;
	case 's':
		player->setPosY(player->getPosY() - 1);
		break;
	case 'd':
		player->setPosX(player->getPosX() + 1);
		break;
	default:
		break;
	}
}

int main(int argc, char* argv[])
{
	MockPlayer * player = new MockPlayer(0,0,0, idle);
	MultiplayerManager * mManager = new MultiplayerManager(player);
	bool quit = false;
	char option;
	map<int, MockPlayer*>::iterator it;
	while (mManager->online() && !mManager->connectionTerminated() && !quit) {
		vector<MockPlayer*> rivals = mManager->getRivals();
		if (rivals.size() > 0) {
			for (vector<MockPlayer*>::iterator it = rivals.begin(); it != rivals.end(); ++it)
			{
				if (*it != NULL) {
					printf("Rival #%d: x --> %d, y --> %d, status --> %d", (*it)->getNumber(), (*it)->getPosX(), (*it)->getPosY(), (*it)->getPlayerStatus());
				}
			}
		}
		else {
			printf("no rivals...\n");
		}


		cin >> option;
		if (option == 'q') {
			quit = true;
		}
		else {
			updatePlayer(player, option);
		}
	}
}


