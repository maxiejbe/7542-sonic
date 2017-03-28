#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include "rapidjson/document.h"
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
	string ReadConfigFileContent(string path);
};

#endif