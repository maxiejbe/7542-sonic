#include "Parser.h"

/* Json parser para archivo de configuración inicial
*/

char* WINDOW_NODE = "ventana";
const char* DIMENSIONS_NODE = "dimensiones";
const char* DIMENSIONS_WIDTH_NODE = "ancho";
const char* DIMENSIONS_HEIGHT_NODE = "alto";

const char* CONFIGURATION_NODE = "configuracion";
const char* CONFIGURATION_SCROLL_SPEED_NODE = "vel_scroll";

char* SCENARIO_NODE = "escenario";

const char* LAYER_NODE = "capas";
const char* LAYER_ID_NODE = "id";
const char* LAYER_ZINDEX_NODE = "index_z";
const char* LAYER_IMAGE_PATH_NODE = "ruta_imagen";

const char* ENTITY_NODE = "entidades";
const char* ENTITY_ID_NODE = "id";
const char* ENTITY_TYPE_NODE = "tipo";
const char* ENTITY_COLOR_NODE = "color";
const char* ENTITY_IMAGE_PATH_NODE = "ruta_imagen";
const char* ENTITY_ZINDEX_NODE = "index_z";

const char* COORDINATE_NODE = "coordenada";
const char* COORDINATE_X_NODE = "x";
const char* COORDINATE_Y_NODE = "y";

Dimensions Parser::ParseDimensions(char* parentNode) {
	if (!document[parentNode].HasMember(DIMENSIONS_NODE)) {
		return Dimensions();
	}

	if (!document[parentNode][DIMENSIONS_NODE].IsObject()) {
		return Dimensions();
	}

	int width;
	if (document[parentNode][DIMENSIONS_NODE].HasMember(DIMENSIONS_WIDTH_NODE) && document[parentNode][DIMENSIONS_NODE][DIMENSIONS_WIDTH_NODE].IsInt()) {
		width = document[parentNode][DIMENSIONS_NODE][DIMENSIONS_WIDTH_NODE].GetInt();
	}

	int height;
	if (document[parentNode][DIMENSIONS_NODE].HasMember(DIMENSIONS_HEIGHT_NODE) && document[parentNode][DIMENSIONS_NODE][DIMENSIONS_HEIGHT_NODE].IsInt()) {
		height = document[parentNode][DIMENSIONS_NODE][DIMENSIONS_WIDTH_NODE].GetInt();
	}
	
	return Dimensions(width, height);
}

vector<Entity> Parser::ParseEntities() {

	if (!document[SCENARIO_NODE].HasMember(ENTITY_NODE)) {
		return vector<Entity>();
	}

	if (!document[SCENARIO_NODE][ENTITY_NODE].IsArray()) {
		return vector<Entity>();
	}

	vector<Entity> entities;
	for (SizeType i = 0; i < document[SCENARIO_NODE][ENTITY_NODE].Size(); i++) {
		entities.push_back(ParseEntity(i));
	}
	return entities;
}

vector<Layer> Parser::ParseLayers() {

	if (!document[SCENARIO_NODE].HasMember(LAYER_NODE)) {
		return vector<Layer>();
	}

	if (!document[SCENARIO_NODE][LAYER_NODE].IsArray()) {
		return vector<Layer>();
	}
	
	vector<Layer> layers;
	for (SizeType i = 0; i < document[SCENARIO_NODE][LAYER_NODE].Size(); i++) {
		layers.push_back(ParseLayer(i));
	}
	return layers;
}

Coordinate Parser::ParseCoordinate(int index) {
	if (!document[SCENARIO_NODE][ENTITY_NODE][index].HasMember(COORDINATE_NODE)) {
		return Coordinate();
	}

	if (!document[SCENARIO_NODE][ENTITY_NODE][index][COORDINATE_NODE].IsObject()) {
		return Coordinate();
	}

	int x;
	if (document[SCENARIO_NODE][ENTITY_NODE][index][COORDINATE_NODE].HasMember(COORDINATE_X_NODE) && document[SCENARIO_NODE][ENTITY_NODE][index][COORDINATE_NODE][COORDINATE_X_NODE].IsInt()) {
		x = document[SCENARIO_NODE][ENTITY_NODE][index][COORDINATE_NODE][COORDINATE_X_NODE].GetInt();
	}

	int y;
	if (document[SCENARIO_NODE][ENTITY_NODE][index][COORDINATE_NODE].HasMember(COORDINATE_Y_NODE) && document[SCENARIO_NODE][ENTITY_NODE][index][COORDINATE_NODE][COORDINATE_Y_NODE].IsInt()) {
		y = document[SCENARIO_NODE][ENTITY_NODE][index][COORDINATE_NODE][COORDINATE_Y_NODE].GetInt();
	}

	return Coordinate(x, y);
}

Entity Parser::ParseEntity(int index) {
	if (!document[SCENARIO_NODE][ENTITY_NODE][index].IsObject()) {
		return Entity();
	}

	int id;
	if (document[SCENARIO_NODE][ENTITY_NODE][index].HasMember(ENTITY_ID_NODE) && document[SCENARIO_NODE][ENTITY_NODE][index][ENTITY_ID_NODE].IsInt()) {
		id = document[SCENARIO_NODE][ENTITY_NODE][index][ENTITY_ID_NODE].GetInt();
	}

	string type;
	if (document[SCENARIO_NODE][ENTITY_NODE][index].HasMember(ENTITY_TYPE_NODE) && document[SCENARIO_NODE][ENTITY_NODE][index][ENTITY_TYPE_NODE].IsString()) {
		type = document[SCENARIO_NODE][ENTITY_NODE][index][ENTITY_TYPE_NODE].GetString();
	}

	string color;
	if (document[SCENARIO_NODE][ENTITY_NODE][index].HasMember(ENTITY_COLOR_NODE) && document[SCENARIO_NODE][ENTITY_NODE][index][ENTITY_COLOR_NODE].IsString()) {
		color = document[SCENARIO_NODE][ENTITY_NODE][index][ENTITY_COLOR_NODE].GetString();
	}

	//Dimensions dimensions = ParseDimensions();
	Coordinate coordinate = ParseCoordinate(index);
	
	string imagePath;
	if (document[SCENARIO_NODE][ENTITY_NODE][index].HasMember(ENTITY_IMAGE_PATH_NODE) && document[SCENARIO_NODE][ENTITY_NODE][index][ENTITY_IMAGE_PATH_NODE].IsString()) {
		imagePath = document[SCENARIO_NODE][ENTITY_NODE][index][ENTITY_IMAGE_PATH_NODE].GetString();
	}

	int zIndex;
	if (document[SCENARIO_NODE][ENTITY_NODE][index].HasMember(ENTITY_ZINDEX_NODE) && document[SCENARIO_NODE][ENTITY_NODE][index][ENTITY_ZINDEX_NODE].IsInt()) {
		zIndex = document[SCENARIO_NODE][ENTITY_NODE][index][ENTITY_ZINDEX_NODE].GetInt();
	}

	return Entity(id, type, color, Dimensions(), coordinate, imagePath, zIndex);
}

Layer Parser::ParseLayer(int index) {
	if (!document[SCENARIO_NODE][LAYER_NODE][index].IsObject()) {
		return Layer();
	}

	int id;
	if (document[SCENARIO_NODE][LAYER_NODE][index].HasMember(LAYER_ID_NODE) && document[SCENARIO_NODE][LAYER_NODE][index][LAYER_ID_NODE].IsInt()) {
		id = document[SCENARIO_NODE][LAYER_NODE][index][LAYER_ID_NODE].GetInt();
	}

	int zIndex;
	if (document[SCENARIO_NODE][LAYER_NODE][index].HasMember(LAYER_ZINDEX_NODE) && document[SCENARIO_NODE][LAYER_NODE][index][LAYER_ZINDEX_NODE].IsInt()) {
		zIndex = document[SCENARIO_NODE][LAYER_NODE][index][LAYER_ZINDEX_NODE].GetInt();
	}

	string imagePath;
	if (document[SCENARIO_NODE][LAYER_NODE][index].HasMember(LAYER_IMAGE_PATH_NODE) && document[SCENARIO_NODE][LAYER_NODE][index][LAYER_IMAGE_PATH_NODE].IsString()) {
		imagePath = document[SCENARIO_NODE][LAYER_NODE][index][LAYER_IMAGE_PATH_NODE].GetString();
	}

	return Layer(id, zIndex, imagePath);
}

Window Parser::ParseWindow() {
	if (!document.HasMember(WINDOW_NODE)) {
		return Window();
	}

	if (!document[WINDOW_NODE].IsObject()) {
		return Window();
	}

	return Window(ParseDimensions(WINDOW_NODE));
}

Configuration Parser::ParseConfiguration() {
	if (!document.HasMember(CONFIGURATION_NODE)) {
		return Configuration();
	}

	if (!document[CONFIGURATION_NODE].IsObject()) {
		return Configuration();
	}

	int scrollSpeed;
	if (document[CONFIGURATION_NODE].HasMember(CONFIGURATION_SCROLL_SPEED_NODE) && document[CONFIGURATION_NODE][CONFIGURATION_SCROLL_SPEED_NODE].IsInt()) {
		scrollSpeed = document[CONFIGURATION_NODE][CONFIGURATION_SCROLL_SPEED_NODE].GetInt();
	}

	return Configuration(scrollSpeed);
}

Scenario Parser::ParseScenario() {
	if (!document.HasMember(SCENARIO_NODE)) {
		return Scenario();
	}

	if (!document[SCENARIO_NODE].IsObject()) {
		return Scenario();
	}

	Dimensions dimensions = ParseDimensions(SCENARIO_NODE);
	vector<Layer> layers = ParseLayers();
	vector<Entity> entities = ParseEntities();

	return Scenario(dimensions, layers, entities);
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
}

Parser::~Parser()
{
}

