#include "Window.h"

char* WINDOW_NODE = "ventana";

Window::Window()
{
}

Window::Window(Dimensions dimensionsParam)
{
	dimensions = dimensionsParam;
}

int Window::getWidth()
{
	return dimensions.getWidth();
}

int Window::getHeight()
{
	return dimensions.getHeight();
}

void Window::Unserialize(Value* nodeRef)
{
	dimensions.ParseObject(nodeRef);
}

char * Window::GetNodeName()
{
	return WINDOW_NODE;
}
