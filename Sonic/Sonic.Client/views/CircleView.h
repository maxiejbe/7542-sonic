#ifndef CIRCLE_VIEW_H
#define CIRCLE_VIEW_H

#include "EntityView.h"
#include "common/Drawable.h"
#include "../utils/img_crop/CircleImageCropper.h"
#include <exception>

class CircleView : public EntityView {
private:
	CircleImageCropper imgCropper;
	bool cropperInitialized;
	void initializeCropper();
	void drawWithImage(SDL_Rect camera);
public:
	CircleView(Entity* entity) : EntityView(entity) {
		cropperInitialized = false;
	}
	
	virtual void draw(SDL_Rect camera) override;
};

#endif // !CIRCLE_H
