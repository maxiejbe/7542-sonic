#include "Parser.h"

/* Json parser para archivo de configuración inicial
*/

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
	fileContent = ReadConfigFileContent(path);
	if (fileContent.empty()) {
		printf("File does not exist (or it's empty).");
	}
	cout << fileContent << std::endl;
}

Parser::~Parser()
{
}

