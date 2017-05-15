#include "ServerConfiguration.h"

char* SERVER_CONFIGURATION_NODE = "servidor";
const char* SERVER_CONFIGURATION_HOST_NUMBER = "host";
const char* SERVER_CONFIGURATION_PORT_NUMBER = "puerto";
const char* SERVER_CONFIGURATION_MAX_ALLOWED_CONNECTIONS = "maxima_cantidad_conexiones";

const char* MESSAGE_PARSING_SERVER_CONFIGURATION_NODE = "Inicio de parseo de nodo configuración de servidor.";
const char* MESSAGE_END_PARSING_SERVER_CONFIGURATION_NODE = "Fin de parseo de nodo configuración de servidor.";

const string DEFAULT_HOST = "192.168.1.10";
const int DEFAULT_PORT_NUMBER = 65535;
const int DEFAULT_MAX_ALLOWED_CONNECTIONS = 10;

ServerConfiguration::ServerConfiguration()
{
}

string ServerConfiguration::getHost()
{
	return this->host;
}

int ServerConfiguration::getPortNumber()
{
	return this->portNumber;
}

int ServerConfiguration::getMaxAllowedClients()
{
	return this->maxAllowedClients;
}

void ServerConfiguration::unserialize(Value * nodeRef)
{
	Value& node = *nodeRef;

	LOG(logINFO) << MESSAGE_PARSING_SERVER_CONFIGURATION_NODE;

	parseString(&host, DEFAULT_HOST, nodeRef, SERVER_CONFIGURATION_HOST_NUMBER);

	parseInt(&portNumber, DEFAULT_PORT_NUMBER, nodeRef, SERVER_CONFIGURATION_PORT_NUMBER, Validator::intGreaterThanZero);

	parseInt(&maxAllowedClients, DEFAULT_MAX_ALLOWED_CONNECTIONS, nodeRef, SERVER_CONFIGURATION_MAX_ALLOWED_CONNECTIONS, Validator::intGreaterThanZero);

	LOG(logINFO) << MESSAGE_END_PARSING_SERVER_CONFIGURATION_NODE;
}

char * ServerConfiguration::getNodeName()
{
	return SERVER_CONFIGURATION_NODE;
}

