#include "Parser.h"

/* Json parser para archivo de configuraci�n inicial
*/

void Parser::Parse(Serializable* serializable) {
	serializable->ParseObject(&document);
}

string Parser::ReadConfigFileContent(string path) {
	ifstream file(path);
	ostringstream tmp;
	tmp << file.rdbuf();
	string content = tmp.str();
	tmp.clear();
	file.close();
	return content;
}

Parser::Parser(string path) {
	string fileContent = ReadConfigFileContent(path);
	if (fileContent.empty()) {
		LOG(logWARNING) << "El archivo '" + path + "' no existe o est� vac�o. Se tomar� uno por defecto."; // TODO: tomar por defecto
	}

	const char *cstr = fileContent.c_str();
	document.Parse(cstr);
}

Parser::~Parser() {
}

