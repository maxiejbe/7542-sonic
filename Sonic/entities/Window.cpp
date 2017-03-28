#include "Window.h"

Window::Window()
{
}

Window::Window(Dimensions dimensionsParam)
{
	dimensions = new Dimensions(dimensionsParam.GetWidth(), dimensionsParam.GetHeight());
}

Dimensions Window::GetDimensions()
{
	return *dimensions;
}
