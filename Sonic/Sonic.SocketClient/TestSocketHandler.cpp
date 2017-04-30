#include "TestSocketHandler.h"

TestSocketHandler::TestSocketHandler()
{
}


TestSocketHandler::~TestSocketHandler()
{
}

void TestSocketHandler::onMessage(char* message)
{
	printf("Mensaje recibido: %s \n", message);
}
