#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include "rapidjson/document.h"

using namespace std;

class Parser {
public:
	Parser(string path);
	~Parser();

private:
	string fileContent;
	string ReadConfigFileContent(string path);
};

#endif