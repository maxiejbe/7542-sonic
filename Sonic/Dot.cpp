//The dot that will move around on the screen
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Dot
{
public:
	//The dimensions of the dot
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	//Maximum axis velocity of the dot
	static const int DOT_VEL = 600; // TODO: tomar del json

	//Initializes the variables
	Dot();

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot
	void move(float timeStep);

	//Shows the dot on the screen relative to the camera
	void render(int camX, int camY);

	//Position accessors
	float getPosX();
	float getPosY();

private:
	float mPosX, mPosY;
	float mVelX, mVelY;
};