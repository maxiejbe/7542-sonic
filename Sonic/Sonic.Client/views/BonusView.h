#ifndef BONUSVIEW_H
#define BONUSVIEW_H

#include "EntityView.h"
#include "SoundManager.h"

class BonusView : public EntityView {
public:
	BonusView(Entity* entity) : EntityView(entity) {
	}
	~BonusView();

	virtual void draw(int camX, int camY) override;

private:
	string getBonusFilePath();
};

#endif // !BONUSVIEW_H
