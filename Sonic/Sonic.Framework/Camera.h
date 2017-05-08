#ifndef CAMERA_H
#define CAMERA_H

#include "entities/Player.h"

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
	~Camera();

	Vector2 getPosition();
	void setXPosition(double x);
	void setYPosition(double y);
	int getWidth();
	int getHeight();
	void setWidth(int w);
	void setHeight(int h);

	// Inherited via Serializable
	void unserialize(Value* nodeRef) override;
	char* getNodeName() override;
	string serialize() override;
private:
	Vector2 position;
	float width, height;
	int screenWidth, screenHeight, scenarioWidth, scenarioHeight;

	void keepCameraInBounds();
	void updateCamera(vector<Player*> players);
	void updatePositionCamera(float x, float y);
};

#endif // !CAMERA_H