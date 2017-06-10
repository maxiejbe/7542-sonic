#ifndef PLAYERUTILS_H
#define PLAYERUTILS_H

#include "entities/Player.h"

class PlayerUtils {
public:

	static string PlayerUtils::getPlayerAvatarFilePath(Player* player);
	static string PlayerUtils::getPlayerName(Player* player);

};

#endif // !PLAYERUTILS_H

