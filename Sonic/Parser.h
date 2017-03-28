#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "entities/Window.h"

using namespace std;
using namespace rapidjson;

class Parser {
public:
	Parser(string path);
	~Parser();
	Window ParseWindow();

private:
	Document document;
	Document windowNode;

	string ReadConfigFileContent(string path);

	Dimensions ParseDimensions();
};

#endif