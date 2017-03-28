#include "Parser.h"

/* Json parser para archivo de configuración inicial
*/

const char* WINDOW_NODE = "ventana";
const char* DIMENSIONS_NODE = "dimensiones";
const char* DIMENSIONS_WIDTH_NODE = "ancho";
const char* DIMENSIONS_HEIGHT_NODE = "alto";

const char* CONFIGURATION_NODE = "configuracion";
const char* CONFIGURATION_SCROLL_SPEED_NODE = "vel_scroll";

Dimensions Parser::ParseDimensions() {
	if (!document[WINDOW_NODE].HasMember(DIMENSIONS_NODE)) {
		return Dimensions();
	}

	int width;
	if (document[WINDOW_NODE][DIMENSIONS_NODE].HasMember(DIMENSIONS_WIDTH_NODE) && document[WINDOW_NODE][DIMENSIONS_NODE][DIMENSIONS_WIDTH_NODE].IsInt()) {
		width = document[WINDOW_NODE][DIMENSIONS_NODE][DIMENSIONS_WIDTH_NODE].GetInt();
	}

	int height;
	if (document[WINDOW_NODE][DIMENSIONS_NODE].HasMember(DIMENSIONS_HEIGHT_NODE) && document[WINDOW_NODE][DIMENSIONS_NODE][DIMENSIONS_HEIGHT_NODE].IsInt()) {
		height = document[WINDOW_NODE][DIMENSIONS_NODE][DIMENSIONS_WIDTH_NODE].GetInt();
	}
	
	return Dimensions(width, height);
}

Window Parser::ParseWindow() {
	if (!document.HasMember(WINDOW_NODE)) {
		return Window();
	}

	if (!document[WINDOW_NODE].IsObject()) {
		return Window();
	}
	
	return Window(ParseDimensions());
}

Configuration Parser::ParseConfiguration() {
	if (!document.HasMember(CONFIGURATION_NODE)) {
		return Configuration();
	}

	int scrollSpeed;
	if (document[CONFIGURATION_NODE].HasMember(CONFIGURATION_SCROLL_SPEED_NODE) && document[CONFIGURATION_NODE][CONFIGURATION_SCROLL_SPEED_NODE].IsInt()) {
		scrollSpeed = document[CONFIGURATION_NODE][CONFIGURATION_SCROLL_SPEED_NODE].GetInt();
	}

	return Configuration(scrollSpeed);
}


string Parser::ReadConfigFileContent(string path)
{
	ifstream file(path);
	ostringstream tmp;
	tmp << file.rdbuf();
	string content = tmp.str();
	tmp.clear();
	file.close();
	return content;
}

Parser::Parser(string path)
{
	string fileContent = ReadConfigFileContent(path);
	if (fileContent.empty()) {
		printf("File does not exist (or it's empty).");
	}
	
	const char *cstr = fileContent.c_str();
	document.Parse(cstr);
}

Parser::~Parser()
{
}

