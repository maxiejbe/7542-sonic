#include "PlayerController.h"

const float gravity = 0.41f;
const float acc = 0.08f;
const int WIDTH_PLAYER_SPRITE = 72; //Fix player->getWidth()
const int INVINCIBLE_SECONDS = 20;
const int RECOVERING_SECONDS = 3;

PlayerController::PlayerController()
{
}

void PlayerController::update(Message* message, Player* player, Camera* camera, Scenario* scenario, int milliseconds)
{
	player->lock();

	player->setTargetVelX(0);
	player->setTime(milliseconds);

	if (message == nullptr) return;
	checkInvincibility(player, milliseconds);
	checkRecovering(player, milliseconds);
	updateInput(message, player);
	move(player, message->getTimeStep(), camera);
	calculateCollisions(player, scenario, camera);

	player->unlock();
}

void PlayerController::updateInput(Message* message, Player* player)
{
	float turboRun = 2;
	float turboSpin = 60;

	if (message->getIsKUTest()) {
		player->setTestMode(!player->getTestMode());
	}

	if (message->getIsKPSpace() && player->getSpriteState() == PlayerStatus::idle) {
		if (player->getFacingDirection() == FACING_RIGHT)
			player->setTargetVelX(player->getScrollSpeed() * turboSpin);
		else
			player->setTargetVelX(player->getScrollSpeed() * -1 * turboSpin);

		player->setSpriteState(PlayerStatus::spinning);
		return;
	}

	if (message->getIsKPLeft() && player->getSpriteState() != PlayerStatus::spinning) {
		player->setFacingDirection(FACING_LEFT);
		player->setTargetVelX(player->getScrollSpeed() * -1);
		if (!player->getIsJumping()) {
			player->setSpriteState(PlayerStatus::walking);
			if (message->getIsKPShift()) {
				player->setTargetVelX(player->getTargetVelX() * turboRun);
				player->setSpriteState(PlayerStatus::running);
			}
		}
	}

	if (message->getIsKPRight() && player->getSpriteState() != PlayerStatus::spinning) {
		player->setFacingDirection(FACING_RIGHT);
		player->setTargetVelX(player->getScrollSpeed());
		if (!player->getIsJumping()) {
			player->setSpriteState(PlayerStatus::walking);
			if (message->getIsKPShift()) {
				player->setTargetVelX(player->getTargetVelX() * turboRun);
				player->setSpriteState(PlayerStatus::running);
			}
		}
	}

	if (message->getIsKPUp() && player->getSpriteState() != PlayerStatus::spinning) {
		if (!player->getIsJumping()) {
			player->setSpriteState(PlayerStatus::jumping);
			player->setIsJumping(true);
			player->setYVelocity(player->getVelocity().y - 10);
		}
	}

	// En caso que se suelten a la vez la flecha y el shift.
	if (message->getIsKULeft() || message->getIsKURight()) {
		if (message->getIsKPShift() || message->getIsKUShift()) {
			player->setSpriteState(PlayerStatus::walking);
		}
	}
}

void PlayerController::move(Player* player, double dt, Camera* camera)
{
	if (player->getIsConnected()) {

		if (abs(player->getVelocity().x) > 100) {
			player->setXVelocity(0);
		}

		// Weighted averaging acceleration method
		player->setXVelocity((acc * player->getTargetVelX() * dt) + ((1 - acc) * player->getVelocity().x));

		// TODO: extraer a isStopping()
		if (fabs(player->getVelocity().x) < 0.4) {
			if (player->getVelocity().x == 0 && (player->getSpriteState() == PlayerStatus::walking
				|| player->getSpriteState() == PlayerStatus::spinning)) {
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

void PlayerController::calculateCollisions(Player * player, Scenario* scenario, Camera* camera)
{
	if (!player->getIsConnected()) return;

	vector<Entity*> entities = scenario->getEntities();
	for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
	{
		if (!(*it)->getIsActive()) continue;
		if (player->isCollisioning(*it)) {
			(*it)->onCollision(player, camera);
		}
	}
}

void PlayerController::checkInvincibility(Player* player, int ms)
{
	if (player->getIsInvincible()) {
		if (player->getInvincibleTime() == 0) {
			player->setInvincibleTime(ms);
		}
		else if (ms - player->getInvincibleTime() >= INVINCIBLE_SECONDS * 1000) {
			player->setIsInvincible(false);
			player->setInvincibleTime(0);
		}
	}
}

void PlayerController::checkRecovering(Player* player, int ms)
{
	if (player->getIsRecovering()) {
		if (player->getRecoveringTime() == 0) {
			player->setRecoveringTime(ms);
		}
		else if (ms - player->getRecoveringTime() >= RECOVERING_SECONDS * 1000) {
			player->setIsRecovering(false);
			player->setRecoveringTime(0);
		}
	}
}