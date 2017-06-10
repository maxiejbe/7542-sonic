#include "PlayerUtils.h"

string PlayerUtils::getPlayerAvatarFilePath(Player* player)
{
	switch (player->getPlayerType()) {
	case SONIC:
		return "img/sonic_avatar.png";
	case TAILS:
		return "img/tails_avatar.png";
	case KNUCKLES:
		return "img/knuckles_avatar.png";
	case SHADOW:
		return "img/shadow_avatar.png";
	default:
		return "img/sonic_avatar.png";
	}
}

string PlayerUtils::getPlayerName(Player* player)
{
	switch (player->getPlayerType()) {
	case SONIC:
		return "SONIC";
	case TAILS:
		return "TAILS";
	case KNUCKLES:
		return "KNUCKLES";
	case SHADOW:
		return "SHADOW";
	default:
		return "SONIC";
	}
}
