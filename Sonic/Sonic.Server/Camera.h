#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
public:
	Camera();
	~Camera();

	Camera getCamera();

private:
	float x,y;

	void keepCameraInBounds();
	void updateCamera();
};

#endif // !CAMERA_H