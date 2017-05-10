#include "Camera.h"

const char* CAMERA_X_POSITION_NODE = "x";
const char* CAMERA_Y_POSITION_NODE = "y";

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


Camera::Camera(Camera & camera)
{
	this->position = Vector2(0, 0);
	this->copyFrom(camera);
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

void Camera::copyFrom(Camera & camera)
{

	this->setXPosition(camera.getPosition().x);
	this->setYPosition(camera.getPosition().y);
	this->setWidth(camera.getWidth());
	this->setHeight(camera.getHeight());
	this->setScreenWidth(camera.getScreenWidth());
	this->setScreenHeight(camera.getScreenHeight());
	this->setScenarioWidth(camera.getScenarioWidth());
	this->setScenarioHeight(camera.getScenarioHeight());
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


void Camera::setScreenWidth(int scw)
{
	this->screenWidth = scw;
}

int Camera::getScreenWidth()
{
	return this->screenWidth;
}

void Camera::setScreenHeight(int sch)
{
	this->screenHeight = sch;
}

int Camera::getScreenHeight()
{
	return this->screenHeight;
}

void Camera::setScenarioWidth(int sw)
{
	this->scenarioWidth = sw;
}

int Camera::getScenarioWidth()
{
	return this->scenarioWidth;
}

void Camera::setScenarioHeight(int sh)
{
	this->scenarioHeight = sh;
}

int Camera::getScenarioHeight()
{
	return this->scenarioHeight;
}
