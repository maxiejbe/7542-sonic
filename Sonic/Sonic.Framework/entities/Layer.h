#ifndef LAYER_H
#define LAYER_H

#include <string>
#include "common/Serializable.h"
#include "common/Validator.h"

using namespace std;

class Layer : public Serializable {
public:
	Layer();

	int getZIndex();
	string getImagePath();
	void setImagePath(string imagePath);
	bool operator< (const Layer &other) const {
		return zIndex < other.zIndex;
	}
private:
	int id;
	int zIndex;
	string imagePath;
	
	// Inherited via Serializable
	virtual void unserialize(Value * nodeRef) override;
	virtual char * getNodeName() override;
};

#endif