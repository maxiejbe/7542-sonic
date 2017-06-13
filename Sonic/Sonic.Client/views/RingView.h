#ifndef RINGVIEW_H
#define RINGVIEW_H

#include "EntityView.h"

class RingView : public EntityView {
public:
	RingView(Entity* entity) : EntityView(entity) {
	}

	virtual void draw(int camX, int camY) override;
};

#endif // !RINGVIEW_H
