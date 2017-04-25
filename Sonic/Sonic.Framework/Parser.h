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
#include "entities/Serializable.h"
#include <vector>
#include "Logger.h"
#include <algorithm>

using namespace std;
using namespace rapidjson;

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