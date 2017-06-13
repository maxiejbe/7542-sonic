#include "PlayerUtils.h"
#include "..\views\PlayerView.h"

string PlayerUtils::getPlayerSpritesheetPath(Player* player)
{
	switch (player->getPlayerType()) {
	case SONIC:
		return "img/sonic-spritesheet.png";
	case TAILS:
		return "img/tails-spritesheet.png";
	case KNUCKLES:
		return "img/knuckles-spritesheet.png";
	case SHADOW:
		return "img/shadow-spritesheet.png";
	default:
		return "img/sonic-spritesheet.png";
	}
}

string PlayerUtils::getDisconnectedPlayerSpritesheetPath(Player* player)
{
	switch (player->getPlayerType()) {
	case SONIC:
		return "img/sonic-spritesheet-grey.png";
	case TAILS:
		return "img/tails-spritesheet-grey.png";
	case KNUCKLES:
		return "img/knuckles-spritesheet-grey.png";
	case SHADOW:
		return "img/shadow-spritesheet-grey.png";
	default:
		return "img/sonic-spritesheet-grey.png";
	}
}

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
