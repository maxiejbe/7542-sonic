#ifndef CAMERA_H
#define CAMERA_H

#include "Player.h"

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

	// Inherited via Serializable
	void unserialize(Value* nodeRef) override;
	char* getNodeName() override;
	string serialize() override;
private:
	void copyFromCamera(Camera& camera);
	Vector2 position;
	float width, height;
	int screenWidth, screenHeight, scenarioWidth, scenarioHeight;
};

#endif // !CAMERA_H