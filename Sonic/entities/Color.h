#ifndef COLOR_H
#define COLOR_H

#include <SDL.h>
#include "../SDLWindow.h"
#include <map>
#include "common/Serializable.h"

class Color : public Serializable {
public:
	Color();
	Color(string color);

	float GetRColor();
	float GetGColor();
	float GetBColor();
	Uint32 GetUint32();
private:
	string color;
	std::map<char, float> RGB;

	void AssignColor(string color);

	// Inherited via Serializable
	virtual void Unserialize(Value * nodeRef) override;
	virtual char * GetNodeName() override;
};

#endif