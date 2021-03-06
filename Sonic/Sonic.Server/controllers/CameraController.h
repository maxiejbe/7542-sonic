#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "entities\Camera.h"

class CameraController
{
public:
	CameraController();
	static void updateCamera(Camera* camera, vector<Player*> players);
private:
	static void keepCameraInBounds(Camera * camera);
	static bool arePlayersInBothBorders(Camera * camera, vector<Player*> players);
};
#endif
