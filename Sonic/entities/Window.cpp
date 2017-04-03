#include "Window.h"

char* WINDOW_NODE = "ventana";

Window::Window()
{
}

Window::Window(Dimensions dimensionsParam)
{
	dimensions = dimensionsParam;
}

int Window::GetWidth()
{
	return dimensions.GetWidth();
}

int Window::GetHeight()
{
	return dimensions.GetHeight();
}

void Window::Unserialize(Value* nodeRef)
{
	dimensions.ParseObject(nodeRef);
}

char * Window::GetNodeName()
{
	return WINDOW_NODE;
}
