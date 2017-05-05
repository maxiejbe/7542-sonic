#include "MultiplayerManager.h"
#include "MockPlayer.h"
#include <time.h>   

//Take a look at: http://stackoverflow.com/questions/16948064/unresolved-external-symbol-lnk2019
using namespace std;

void updatePlayer(MockPlayer * player, char option) {
	switch (option)
	{
	case 'w':
		player->setPosition(player->getPosition().y + 1);
		break;
	case 'a':
		player->setPosX(player->getPosition().x - 1);
		break;
	case 's':
		player->setPosY(player->getPosition().y - 1);
		break;
	case 'd':
		player->setPosX(player->getPosition().x + 1);
		break;
	default:
		break;
	}
}

int main(int argc, char* argv[])
{
	MockPlayer * player = new MockPlayer(-1,0,0, idle);
	MultiplayerManager * mManager = new MultiplayerManager(player);
	bool quit = false;
	char option;
	map<int, MockPlayer*>::iterator it;
	while (mManager->online() && !mManager->connectionTerminated() && !quit) {
		if (player->getNumber() > 0) {
			printf("Current Player #%d: x-->%d, y-->%d, status --> %d \n\n", player->getNumber(), player->getPosX(), player->getPosY(), player->getPlayerStatus());
			vector<MockPlayer*> rivals = mManager->getRivals();
			if (rivals.size() > 0) {
				for (vector<MockPlayer*>::iterator it = rivals.begin(); it != rivals.end(); ++it)
				{
					if (*it != NULL) {
						printf("Rival #%d: x --> %d, y --> %d, status --> %d \n", (*it)->getNumber(), (*it)->getPosX(), (*it)->getPosY(), (*it)->getPlayerStatus());
					}
				}
			}
			else {
				printf("no rivals...\n");
			}

			printf("ingrese un movimiento: ");
			cin >> option;
			if (option == 'q') {
				quit = true;
			}
			else {
				updatePlayer(player, option);
			}
			printf("\n\n");
		}
	}
}


