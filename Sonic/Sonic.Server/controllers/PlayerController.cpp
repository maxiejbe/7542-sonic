#include "PlayerController.h"

const float gravity = 0.38f;

void PlayerController::update(Player* player, float dt)
{
	player->setTargetVelX(0);

	updateInput(player);
	move(player, dt);
}

void PlayerController::updateInput(Player* player)
{
	/*float turbo = 2;

	if (input->isKeyPressed(KEY_LEFT)) {
		player->setFacingDirection(FACING_LEFT);
		player->setTargetVelX(player->getScrollSpeed() * -1);
		if (!player->getIsJumping()) {
			player->setSpriteState(PlayerStatus::walking);
			if (input->isKeyPressed(KEY_SPACE)) {
				player->setTargetVelX(player->getTargetVelX() * turbo);
				player->setSpriteState(PlayerStatus::running);
			}
		}
	}

	if (input->isKeyPressed(KEY_RIGHT)) {
		player->setFacingDirection(FACING_RIGHT);
		player->setTargetVelX(player->getScrollSpeed());
		if (!player->getIsJumping()) {
			player->setSpriteState(PlayerStatus::walking);
			if (input->isKeyPressed(KEY_SPACE)) {
				player->setTargetVelX(player->getTargetVelX() * turbo);
				player->setSpriteState(PlayerStatus::running);
			}
		}
	}

	if (input->isKeyPressed(KEY_UP)) {
		// TODO: extraer a PlayerStatus::jumping()
		if (!player->getIsJumping()) {
			player->setSpriteState(PlayerStatus::jumping);
			player->setIsJumping(true);
			player->setYVelocity(player->getVelocity().y - 10);
		}
	}

	// En caso que se suelten a la vez la flecha y el space.
	if (input->isKeyUp(KEY_LEFT) || input->isKeyUp(KEY_RIGHT)) {
		if (input->isKeyPressed(KEY_SPACE) || input->isKeyUp(KEY_SPACE)) {
			player->setSpriteState(PlayerStatus::walking);
		}
	}*/
}

void PlayerController::move(Player* player, float dt)
{
	// Weighted averaging acceleration method
	float a = 0.08;
	player->setXVelocity((a * player->getTargetVelX() * dt) + ((1 - a) * player->getVelocity().x));

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
	else if (player->getPosition().x > player->getScenarioWidth() - player->getWidth())
		player->setXPosition((float)(player->getScenarioWidth() - player->getWidth()));

	// PlayerStatus::jumping
	if (player->getIsJumping()) {
		player->setYVelocity(player->getVelocity().y + gravity);

		if ((player->getPosition().y + player->getVelocity().y) >= player->getGroundPos()) {
			player->setYVelocity(0);
			player->setIsJumping(false);
			player->setSpriteState(PlayerStatus::idle);
		}

		player->setYPosition(player->getPosition().y + player->getVelocity().y * 1.6);
	}
}