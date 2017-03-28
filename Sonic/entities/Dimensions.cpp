#include "Dimensions.h"

Dimensions::Dimensions()
{
}

Dimensions::Dimensions(int widthParam, int heightParam)
{
	width = widthParam;
	height = heightParam;
}

int Dimensions::GetWidth()
{
	return width;
}

int Dimensions::GetHeight()
{
	return height;
}
