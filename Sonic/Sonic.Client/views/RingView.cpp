#include "RingView.h"

void RingView::draw(SDL_Rect camera) {

	if (this->entity->getImagePath() != "") {
		this->entity->setImagePath("img/ring.png");
	}

	CircleView::draw(camera);
}

