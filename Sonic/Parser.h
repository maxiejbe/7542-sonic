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
#include <vector>

using namespace std;
using namespace rapidjson;

//TODO Maxi: Extract to base methods ParseObject and ParseCollection with generics
//Unserealization would be responsibility of each object

class Parser {
public:
	Parser(string path);
	~Parser();
	Window ParseWindow();
	Configuration ParseConfiguration();
	void ParseScenario(Scenario* scenario);

private:
	Document document;
	Document windowNode;

	string ReadConfigFileContent(string path);

	Dimensions ParseDimensions(Value* parentNodeRef);
	Layer ParseLayer(Value* parentNodeRef);
	Entity ParseEntity(Value* parentNodeRef);
	Coordinate ParseCoordinate(Value* parentNodeRef);

	vector<Layer> ParseLayers(Value* parentNodeRef);
	vector<Entity> ParseEntities(Value* parentNodeRef);

};

#endif