#include "CameraController.h"

const int BORDER_WIDTH = 100;

CameraController::CameraController()
{
}


void CameraController::updateCamera(Camera * camera, vector<Player*> players)
{
	float x, y = 0;
	float befX = camera->getPosition().x;
	float befY = camera->getPosition().y;
	bool playerIsInLeftBorder = false, playerIsInRightBorder = false;
	int rightBorder = camera->getPosition().x + camera->getScreenHeight() - BORDER_WIDTH;
	int leftBorder = camera->getPosition().x + BORDER_WIDTH;

	vector<Player*>::iterator it = players.begin();
	while (it != players.end()) {
		Player* currentPlayer = (*it);

		//Players uno en cada borde, camara no se mueve (queda como estaba antes)
		if (playerIsInLeftBorder && playerIsInRightBorder)
		{
			camera->setXPosition(befX);
			camera->setYPosition(befY);
			break;
		}

		y = ((int)currentPlayer->getPosition().y + currentPlayer->getHeight() / 2) - camera->getScreenWidth() / 2;
		if (currentPlayer->getPosition().x > rightBorder)
		{
			playerIsInRightBorder = true;
			x = camera->getPosition().x + currentPlayer->getPosition().x - rightBorder;
			updateCameraPostion(camera, x, y);
		}
		if (currentPlayer->getPosition().x < leftBorder)
		{
			playerIsInLeftBorder = true;
			x = camera->getPosition().x + currentPlayer->getPosition().x - leftBorder;
			updateCameraPostion(camera, x, y);
		}

		it++;
	}

	keepCameraInBounds(camera);
}

void CameraController::keepCameraInBounds(Camera * camera)
{
	if (camera->getPosition().x < 0)
		camera->setXPosition(0);
	if (camera->getPosition().y < 0)
		camera->setYPosition(0);
	if (camera->getPosition().x >(camera->getScenarioWidth() - camera->getWidth()))
		camera->setXPosition(camera->getScenarioWidth() - camera->getWidth());
	if (camera->getPosition().y >(camera->getScenarioHeight() - camera->getHeight()))
		camera->setYPosition(camera->getScenarioHeight() - camera->getHeight());
}

void CameraController::updateCameraPostion(Camera * camera, float x, float y)
{
	camera->setXPosition(x);
	camera->setYPosition(y);
}

