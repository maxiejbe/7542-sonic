#ifndef CAMERA_H
#define CAMERA_H

#include "Player.h"
#include <mutex>

class Camera : public Serializable
{
public:
	Camera();
	Camera(int x, int y, int w, int h, int screenWidth, int screenHeight, int scenarioWidth, int scenarioHeight) : Camera() {
		this->position = Vector2(x, y);
		this->width = w;
		this->height = h;
		this->screenWidth = screenWidth;
		this->screenHeight = screenHeight;
		this->scenarioWidth = scenarioWidth;
		this->scenarioHeight = scenarioHeight;
	}
	Camera(Camera & camera);

	~Camera();

	string getSerializedCamera();

	void lock();
	void unlock();

	Vector2 getPosition();
	void setXPosition(double x);
	void setYPosition(double y);
	int getWidth();
	int getHeight();
	void setWidth(int w);
	void setHeight(int h);
	void setScreenWidth(int scw);
	int getScreenWidth();
	void setScreenHeight(int sch);
	int getScreenHeight();
	void setScenarioWidth(int sw);
	int getScenarioWidth();
	void setScenarioHeight(int sh);
	int getScenarioHeight();

	void copyFrom(Camera& camera);
	// Inherited via Serializable
	void unserialize(Value* nodeRef) override;
	char* getNodeName() override;
	string serialize() override;
	void serializeCamera();

private:
	string serializedCamera;
	mutex cameraMutex;

	Vector2 position;
	int width, height;
	int screenWidth, screenHeight, scenarioWidth, scenarioHeight;
};

#endif // !CAMERA_H