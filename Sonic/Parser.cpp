#include "Parser.h"

const string DEFAULT_CONFIG_FILE = "config/params.json";
const char* MESSAGE_USING_CONFIG_FILE = "Archivo de configuración utilizado: ";
const char* MESSAGE_NO_CONFIG_FILE_PARAM = "No se especificó un archivo de configuración.";
const char* MESSAGE_USING_DEFAULT_CONFIG_FILE = "El archivo no existe. Utilizando el default.";
const char* MESSAGE_EMPTY_CONFIG_FILE = "El archivo está vacío. Utilizando el default.";
const char* MESSAGE_CANNOT_PARSE_CONFIG_FILE = "El archivo no es un json. Utilizando el default.";


/* Json parser para archivo de configuración inicial
*/

void Parser::Parse(Serializable* serializable) {
	serializable->ParseObject(&document);
}

bool Parser::ReadConfigFileContent(string path)
{
	if (path.empty()) {
		LOG(logWARNING) << MESSAGE_NO_CONFIG_FILE_PARAM;
		return false;
	}

	LOG(logINFO) << MESSAGE_USING_CONFIG_FILE + path;
	
	ifstream file(path);
	if (!file.good()) {
		file.close();
		file.clear();
		LOG(logWARNING) << MESSAGE_USING_DEFAULT_CONFIG_FILE;
		return false;
	}

	ostringstream tmp;
	tmp << file.rdbuf();
	fileContent.clear();
	fileContent = tmp.str();
	transform(fileContent.begin(), fileContent.end(), fileContent.begin(), ::tolower);
	tmp.clear();

	file.close();
	file.clear();
	
	if (fileContent.empty()) {
		LOG(logWARNING) << MESSAGE_EMPTY_CONFIG_FILE;
		return false;
	}
	
	return true;
}

bool Parser::ParseDocument()
{
	const char *cstr = fileContent.c_str();
	if (document.Parse(cstr).HasParseError()) {
		LOG(logERROR) << MESSAGE_CANNOT_PARSE_CONFIG_FILE;
		return false;
	}
	return true;
}

Parser::Parser(string path)
{
	if (!ReadConfigFileContent(path)) {
		ReadConfigFileContent(DEFAULT_CONFIG_FILE);
	}

	if (!ParseDocument()) {
		ReadConfigFileContent(DEFAULT_CONFIG_FILE);
		ParseDocument();
	}
}

Parser::~Parser()
{
}

