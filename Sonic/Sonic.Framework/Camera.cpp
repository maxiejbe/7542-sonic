#include "Camera.h"

const char* CAMERA_X_POSITION_NODE = "x";
const char* CAMERA_Y_POSITION_NODE = "y";
const int BORDER_WIDTH = 100;

Camera::Camera()
{
	this->position = Vector2(0, 0);
	this->width = 0;
	this->height = 0;
	this->screenWidth = 0;
	this->screenHeight = 0;
	this->scenarioWidth = 0;
	this->scenarioHeight = 0;
}


Camera::~Camera()
{
}

Vector2 Camera::getPosition()
{
	return this->position;
}

void Camera::setXPosition(double x)
{
	this->position.x = x;
}

void Camera::setYPosition(double y)
{
	this->position.y = y;
}

void Camera::setWidth(int w)
{
	this->width = w;
}

int Camera::getWidth()
{
	return this->width;
}

void Camera::setHeight(int h)
{
	this->height = h;
}

int Camera::getHeight()
{
	return this->height;
}

char * Camera::getNodeName()
{
	return nullptr;
}

string Camera::serialize()
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);
	writer.StartObject();

	writer.String(CAMERA_X_POSITION_NODE);
	writer.Double(this->getPosition().x);
	writer.String(CAMERA_Y_POSITION_NODE);
	writer.Double(this->getPosition().y);

	writer.EndObject();
	return s.GetString();
}

void Camera::unserialize(Value * nodeRef)
{
	double x, y = 0;
	//position x
	parseDouble(&x, 0, nodeRef, CAMERA_X_POSITION_NODE);
	this->setXPosition(x);
	//position y
	parseDouble(&y, 0, nodeRef, CAMERA_Y_POSITION_NODE);
	this->setYPosition(y);
}

//Solo update cuando hay un player en un solo borde
void Camera::updateCamera(vector<Player*> players)
{
	float x, y = 0;
	float befX = this->getPosition().x;
	float befY = this->getPosition().y;
	bool playerIsInLeftBorder, playerIsInRightBorder = false;
	int rightBorder = this->getPosition().x + this->screenWidth - BORDER_WIDTH;
	int leftBorder = this->getPosition().x + BORDER_WIDTH;

	vector<Player*>::iterator it = players.begin();
	while (it != players.end()) {
		Player* currentPlayer = (*it);

		//Players uno en cada borde, camara no se mueve (queda como estaba antes)
		if (playerIsInLeftBorder && playerIsInRightBorder) 
		{ 
			this->setXPosition(befX);
			this->setYPosition(befY);
			break; 
		}
		
		y = ((int)currentPlayer->getPosition().y + currentPlayer->getHeight() / 2) - this->screenWidth / 2;
		if (currentPlayer->getPosition().x > rightBorder) 
		{ 
			playerIsInRightBorder = true;
			x = this->getPosition().x + currentPlayer->getPosition().x - rightBorder;
			this->updatePositionCamera(x, y);
		}
		if (currentPlayer->getPosition().x < leftBorder) 
		{ 
			playerIsInLeftBorder = true;
			x = this->getPosition().x + currentPlayer->getPosition().x - leftBorder;
			this->updatePositionCamera(x, y);
		}

		it++;
	}

	this->keepCameraInBounds();
}

void Camera::keepCameraInBounds()
{
	if (this->getPosition().x < 0)
		this->setXPosition(0);
	if (this->getPosition().y < 0)
		this->setYPosition(0);
	if (this->getPosition().x > (this->scenarioWidth - this->getWidth()))
		this->setXPosition(this->scenarioWidth - this->getWidth());
	if (this->getPosition().y > (this->scenarioHeight - this->getHeight()))
		this->setYPosition(this->scenarioHeight - this->getHeight());
}

void Camera::updatePositionCamera(float x, float y)
{
	this->setXPosition(x);
	this->setYPosition(y);
}