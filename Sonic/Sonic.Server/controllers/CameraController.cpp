#include "CameraController.h"

const int RIGHT_BORDER_WIDTH = 100;
const int LEFT_BORDER_WIDTH = 30;

CameraController::CameraController()
{
}


void CameraController::updateCamera(Camera * camera, vector<Player*> players)
{
	camera->lock();

	int rightBorder = camera->getPosition().x + camera->getScreenWidth() - RIGHT_BORDER_WIDTH;
	int leftBorder = camera->getPosition().x + LEFT_BORDER_WIDTH;

	if (!arePlayersInBothBorders(camera, players)) {
		for (Player* currentPlayer : players) {
			if (currentPlayer->getIsConnected()) {

				camera->setYPosition(((int)currentPlayer->getPosition().y + currentPlayer->getHeight() / 2) - camera->getScreenWidth() / 2);

				if (currentPlayer->getPosition().x > rightBorder)
					camera->setXPosition(camera->getPosition().x + currentPlayer->getPosition().x - rightBorder);

				if (currentPlayer->getPosition().x < leftBorder)
					camera->setXPosition(camera->getPosition().x + currentPlayer->getPosition().x - leftBorder);
			}

			keepCameraInBounds(camera);
		}
	}

	camera->unlock();
}

void CameraController::keepCameraInBounds(Camera * camera)
{
	if (camera->getPosition().x < 0)
		camera->setXPosition(0);
	if (camera->getPosition().y < 0)
		camera->setYPosition(0);
	if (camera->getPosition().x > (camera->getScenarioWidth() - camera->getWidth()))
		camera->setXPosition(camera->getScenarioWidth() - camera->getWidth());
	if (camera->getPosition().y > (camera->getScenarioHeight() - camera->getHeight()))
		camera->setYPosition(camera->getScenarioHeight() - camera->getHeight());
}

bool CameraController::arePlayersInBothBorders(Camera * camera, vector<Player*> players)
{
	bool playerIsInRightBorder = false;
	bool playerIsInLeftBorder = false;

	int rightBorder = camera->getPosition().x + camera->getScreenWidth() - RIGHT_BORDER_WIDTH;
	int leftBorder = camera->getPosition().x + LEFT_BORDER_WIDTH;

	for (Player* currentPlayer : players) {

		if (currentPlayer->getPosition().x > rightBorder && currentPlayer->getIsConnected())
			playerIsInRightBorder = true;

		if (currentPlayer->getPosition().x < leftBorder && currentPlayer->getIsConnected())
			playerIsInLeftBorder = true;
	}

	return (playerIsInLeftBorder && playerIsInRightBorder);
}

