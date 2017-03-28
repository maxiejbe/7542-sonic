#include "Dimensions.h"

Dimensions::Dimensions()
{
}

Dimensions::Dimensions(int widthParam, int heightParam, int radioParam)
{
	width = widthParam;
	height = heightParam;
	radio = radioParam;
}

int Dimensions::GetWidth()
{
	return width;
}

int Dimensions::GetHeight()
{
	return height;
}
