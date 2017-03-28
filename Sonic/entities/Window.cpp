#include "Window.h"

char* WINDOW_NODE = "ventana";

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

void Window::Unserialize(Value* nodeRef)
{
	dimensions.ParseObject(nodeRef);
}

char * Window::GetNodeName()
{
	return WINDOW_NODE;
}
