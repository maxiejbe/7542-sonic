#include "PlayerController.h"

const float gravity = 0.41f;
const float acc = 0.08f;
const int WIDTH_PLAYER_SPRITE = 72; //Fix player->getWidth()

PlayerController::PlayerController()
{
}

void PlayerController::update(Message* message, Player* player, Camera* camera)
{
	player->lock();

	player->setTargetVelX(0);
	if (message == nullptr) return;
	updateInput(message, player);
	move(player, message->getTimeStep(), camera);

	player->unlock();
}

void PlayerController::updateInput(Message* message, Player* player)
{
	float turbo = 2;

	if (message->getIsKPLeft()) {
		player->setFacingDirection(FACING_LEFT);
		player->setTargetVelX(player->getScrollSpeed() * -1);
		if (!player->getIsJumping()) {
			player->setSpriteState(PlayerStatus::walking);
			if (message->getIsKPSpace()) {
				player->setTargetVelX(player->getTargetVelX() * turbo);
				player->setSpriteState(PlayerStatus::running);
			}
		}
	}

	if (message->getIsKPRight()) {
		player->setFacingDirection(FACING_RIGHT);
		player->setTargetVelX(player->getScrollSpeed());
		if (!player->getIsJumping()) {
			player->setSpriteState(PlayerStatus::walking);
			if (message->getIsKPSpace()) {
				player->setTargetVelX(player->getTargetVelX() * turbo);
				player->setSpriteState(PlayerStatus::running);
			}
		}
	}

	if (message->getIsKPUp()) {
		// TODO: extraer a PlayerStatus::jumping()
		if (!player->getIsJumping()) {
			player->setSpriteState(PlayerStatus::jumping);
			player->setIsJumping(true);
			player->setYVelocity(player->getVelocity().y - 10);
		}
	}

	// En caso que se suelten a la vez la flecha y el space.
	if (message->getIsKULeft() || message->getIsKURight()) {
		if (message->getIsKPSpace() || message->getIsKUSpace()) {
			player->setSpriteState(PlayerStatus::walking);
		}
	}
}

void PlayerController::move(Player* player, double dt, Camera* camera)
{
	if (player->getIsConnected()) {

		if (player->getVelocity().x < -100) {
  			player->setXVelocity(0);
		}

		// Weighted averaging acceleration method
		player->setXVelocity((acc * player->getTargetVelX() * dt) + ((1 - acc) * player->getVelocity().x));

		// TODO: extraer a isStopping()
		if (fabs(player->getVelocity().x) < 0.4) {
			if (player->getVelocity().x == 0 && player->getSpriteState() == PlayerStatus::walking) {
				player->setSpriteState(PlayerStatus::idle);
			}
			player->setXVelocity(0);
		}

		player->setXPosition(player->getPosition().x + player->getVelocity().x);

		// Que no se salga de los limites
		if (player->getPosition().x < 0)
			player->setXPosition(0);
		else if (player->getPosition().x > player->getScenarioWidth() - WIDTH_PLAYER_SPRITE)
			player->setXPosition((float)(player->getScenarioWidth() - WIDTH_PLAYER_SPRITE));

		// Que no se salga de la camara
		if (player->getPosition().x < camera->getPosition().x)
			player->setXPosition(camera->getPosition().x);
		else if (player->getPosition().x > (camera->getPosition().x + camera->getScreenWidth()) - WIDTH_PLAYER_SPRITE)
			player->setXPosition(camera->getPosition().x + camera->getScreenWidth() - WIDTH_PLAYER_SPRITE);

		// PlayerStatus::jumping
		if (player->getIsJumping()) {
			player->setYVelocity(player->getVelocity().y + gravity);

			if ((player->getPosition().y + player->getVelocity().y) >= player->getGroundPos()) {
				player->setYVelocity(0);
				player->setIsJumping(false);
				player->setSpriteState(PlayerStatus::idle);
				player->setYPosition(player->getGroundPos());
			}

			player->setYPosition(player->getPosition().y + player->getVelocity().y * 1.45);

		}
	}
	else {
		if (player->getPosition().x <= camera->getPosition().x) {
			player->setXPosition(camera->getPosition().x);
		}
		if (player->getPosition().x >= (camera->getPosition().x + camera->getScreenWidth() - WIDTH_PLAYER_SPRITE)) {
			player->setXPosition(camera->getPosition().x + camera->getScreenWidth() - WIDTH_PLAYER_SPRITE);
		}
	}
}