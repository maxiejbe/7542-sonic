#include "Color.h"

char* COLOR_NODE = "color";
const char* COLOR_RED_NODE = "rojo";
const char* COLOR_YELLOW_NODE = "amarillo";
const char* COLOR_GREEN_NODE = "verde";

const char* MESSAGE_PARSING_COLOR_NODE = "Inicio de parseo de nodo color.";
const char* MESSAGE_END_PARSING_COLOR_NODE = "Fin de parseo de nodo color.";

const char* COLOR_DEFAULT = COLOR_RED_NODE;

Color::Color()
{
	//Default color red
	AssignColor(COLOR_DEFAULT);
}

Color::Color(string color)
{
	AssignColor(color);
}

void Color::Unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;

	LOG(logINFO) << MESSAGE_PARSING_COLOR_NODE;

	ParseString(&color, COLOR_DEFAULT, nodeRef, COLOR_NODE);

	LOG(logINFO) << MESSAGE_END_PARSING_COLOR_NODE;
}

char * Color::GetNodeName()
{
	return COLOR_NODE;
}

float Color::GetRColor()
{
	return RGB['R'];
}

float Color::GetGColor()
{
	return RGB['G'];
}

float Color::GetBColor()
{
	return RGB['B'];
}

Uint32 Color::GetUint32() {
	Uint32 colorCode = 0;
	if (SDLWindow::getInstance().gWindow != NULL) {
		colorCode = SDL_MapRGBA(SDL_GetWindowSurface(SDLWindow::getInstance().gWindow)->format, GetRColor(),GetGColor(), GetBColor(),255);
	}
	else {
		LOG(logERROR) << "No se puede recuperar el color en formato Uint32 - Error: La ventana es nula";
	}

	return colorCode;
}


void Color::AssignColor(string color)
{
	bool colorSet = false;
	if (color == COLOR_RED_NODE)
	{
		RGB['R'] = 255;
		RGB['G'] = 0;
		RGB['B'] = 0;
		colorSet = true;
	}
	if (color == COLOR_YELLOW_NODE)
	{
		RGB['R'] = 255;
		RGB['G'] = 255;
		RGB['B'] = 0;
		colorSet = true;
	}
	if (color == COLOR_GREEN_NODE)
	{
		RGB['R'] = 0;
		RGB['G'] = 128;
		RGB['B'] = 0;
		colorSet = true;
	}

	if (!colorSet) {
		AssignColor(COLOR_DEFAULT);
	}

}