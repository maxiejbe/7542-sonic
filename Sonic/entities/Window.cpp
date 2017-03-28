#include "Window.h"

Window::Window()
{
}

Window::Window(Dimensions dimensionsParam)
{
	dimensions = dimensionsParam;
}

Dimensions Window::GetDimensions()
{
	return dimensions;
}
