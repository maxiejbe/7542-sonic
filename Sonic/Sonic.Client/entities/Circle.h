#ifndef CIRCLE_H
#define CIRCLE_H

#include "Entity.h"
#include "common/Drawable.h"
#include "../utils/img_crop/CircleImageCropper.h"
#include <exception>

class Circle : public Entity {
private:
	CircleImageCropper imgCropper;
	bool cropperInitialized;
	void initializeCropper();
	void drawWithImage(SDL_Rect camera);
public:
	Circle();
	Circle(Entity* entity);
	virtual void draw(SDL_Rect camera) override;
	
	virtual Dimensions getDefaultDimensions() override;
};

#endif // !CIRCLE_H
