#include "Parser.h"

/* Json parser para archivo de configuración inicial
*/

Window Parser::ParseWindow() {
	return Window();
}

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
	string fileContent = ReadConfigFileContent(path);
	if (fileContent.empty()) {
		printf("File does not exist (or it's empty).");
	}
	
	const char *cstr = fileContent.c_str();
	document.Parse(cstr);

	printf(document.IsObject() ? "true" : "false");
	//cout << fileContent << std::endl;
}

Parser::~Parser()
{
}

