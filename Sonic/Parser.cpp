#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include "rapidjson/document.h"

/* Json parser para archivo de configuración inicial
*/

using namespace std;

class Parser {
public:
	Parser(string path);
	~Parser();

private:
	string ReadConfigFileContent(string path);
};

inline Parser::Parser(string path)
{
	string content = ReadConfigFileContent(path);
	if (content.empty()) {
		printf("File does not exist (or it's empty).");
	}
	//cout << content << std::endl;
}

inline Parser::~Parser()
{
}

inline string Parser::ReadConfigFileContent(string path)
{
	ifstream file(path);
	ostringstream tmp;
	tmp << file.rdbuf();
	string content = tmp.str();
	tmp.clear();
	file.close();
	return content;
}