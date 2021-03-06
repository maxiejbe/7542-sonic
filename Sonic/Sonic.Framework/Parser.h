#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <document.h>
#include <writer.h>
#include <stringbuffer.h>
#include "entities/common/Serializable.h"
#include <vector>
#include "Logger.h"
#include "entities/Level.h"
#include <algorithm>

using namespace std;
using namespace rapidjson;

class Parser {
public:
	Parser(string path, string content);
	~Parser();
	void parse(Serializable* serializable);

	string getFileContent();
private:
	Document document;
	Document windowNode;

	bool readConfigFileContent(string path);
	bool parseDocument();

	string fileContent;
};

#endif
