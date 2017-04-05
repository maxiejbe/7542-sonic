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
#include "entities/Configuration.h"
#include "entities/Scenario.h"
#include "entities/Coordinate.h"
#include "entities/common/Serializable.h"
#include <vector>
#include "Logger.h"
#include <algorithm>

using namespace std;
using namespace rapidjson;

//TODO Maxi: Extract to base methods ParseObject and ParseCollection with generics
//Unserealization would be responsibility of each object

class Parser {
public:
	Parser(string path);
	~Parser();
	void parse(Serializable* serializable);
private:
	Document document;
	Document windowNode;

	bool readConfigFileContent(string path);
	bool parseDocument();

	string fileContent;
};

#endif