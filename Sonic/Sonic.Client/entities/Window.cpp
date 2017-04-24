#include "Window.h"

char* WINDOW_NODE = "ventana";

const char* MESSAGE_PARSING_WINDOW_NODE = "Inicio de parseo de nodo ventana.";
const char* MESSAGE_END_PARSING_WINDOW_NODE = "Fin de parseo de nodo ventana.";

const int WINDOW_DEFAULT_WIDTH = 800;
const int WINDOW_DEFAULT_HEIGHT = 600;
const int WINDOW_DEFAULT_RADIO = 0;

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

void Window::unserialize(Value* nodeRef)
{
	LOG(logINFO) << MESSAGE_PARSING_WINDOW_NODE;

	dimensions.setDefaults(WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT, WINDOW_DEFAULT_RADIO);
	dimensions.parseObject(nodeRef);

	LOG(logINFO) << MESSAGE_END_PARSING_WINDOW_NODE;
}

char * Window::getNodeName()
{
	return WINDOW_NODE;
}
