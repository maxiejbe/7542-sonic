#ifndef SCENARIO_H
#define SCENARIO_H

#include "Dimensions.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Square.h"
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
	void SetDimensions(Dimensions);
	void SetLayers(vector<Layer>);
	void SetEntities(vector<Entity*>);

	vector<Entity*> GetEntities();

	int GetWidth();
	int GetHeight();
private:
	Dimensions dimensions;
	vector<Layer> layers;
	vector<Entity*> entities;
	
	// Inherited via Serializable
	virtual void Unserialize(Value * nodeRef) override;
	virtual char * GetNodeName() override;
};

#endif