#ifndef COLOR_H
#define COLOR_H

#include <map>
#include "common/Serializable.h"

class Color : public Serializable {
public:
	Color();
	Color(string color);

	float GetRColor();
	float GetGColor();
	float GetBColor();

private:
	string color;
	std::map<char, float> RGB;

	void AssignColor(string color);

	// Inherited via Serializable
	virtual void Unserialize(Value * nodeRef) override;
	virtual char * GetNodeName() override;
};

#endif