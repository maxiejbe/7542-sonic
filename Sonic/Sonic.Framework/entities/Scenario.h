#ifndef SCENARIO_H
#define SCENARIO_H

#include "Dimensions.h"
#include "common/EntityResolver.h"
#include "Entity.h"
#include "Layer.h"
#include <iostream>
#include <vector>

using namespace std;

class Scenario : public Serializable {
public:
	Scenario();
	~Scenario();

	vector<Layer> getLayers();
	void setDimensions(Dimensions);
	void setLayers(vector<Layer>);
	void setEntities(vector<Entity*>);

	vector<Entity*> getEntities();

	int getWidth();
	int getHeight();

	void serializeLayers(Writer<StringBuffer>& writer);
	// Inherited via Serializable
	virtual string serialize() override;
	virtual void unserialize(Value * nodeRef) override;
	virtual char * getNodeName() override;
private:
	Dimensions dimensions;
	vector<Layer> layers;
	vector<Entity*> entities;
};

#endif