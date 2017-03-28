#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include "rapidjson/document.h"

class Parser {
public:
	Parser(std::string path);
	~Parser();

private:
	std::string fileContent;
	std::string ReadConfigFileContent(std::string path);
};

#endif