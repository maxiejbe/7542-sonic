#include "Parser.h"

/* Json parser para archivo de configuración inicial
*/

char* WINDOW_NODE = "ventana";
const char* DIMENSIONS_NODE = "dimensiones";
const char* DIMENSIONS_WIDTH_NODE = "ancho";
const char* DIMENSIONS_HEIGHT_NODE = "alto";
const char* DIMENSIONS_RADIO_NODE = "radio";

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

Dimensions Parser::ParseDimensions(Value* parentNodeRef) {
	Value& parentNode = *parentNodeRef;

	if (!parentNode.HasMember(DIMENSIONS_NODE)) {
		return Dimensions();
	}

	Value& childNode = parentNode[DIMENSIONS_NODE];
	if (!childNode.IsObject()) {
		return Dimensions();
	}

	int width = 0;
	if (childNode.HasMember(DIMENSIONS_WIDTH_NODE) && childNode[DIMENSIONS_WIDTH_NODE].IsInt()) {
		width = childNode[DIMENSIONS_WIDTH_NODE].GetInt();
	}

	int height = 0;
	if (childNode.HasMember(DIMENSIONS_HEIGHT_NODE) && childNode[DIMENSIONS_HEIGHT_NODE].IsInt()) {
		height = childNode[DIMENSIONS_HEIGHT_NODE].GetInt();
	}

	int radio = 0;
	if (childNode.HasMember(DIMENSIONS_RADIO_NODE) && childNode[DIMENSIONS_RADIO_NODE].IsInt()) {
		radio = childNode[DIMENSIONS_RADIO_NODE].GetInt();
	}
	
	return Dimensions(width, height, radio);
}

vector<Entity> Parser::ParseEntities(Value* parentNodeRef) {
	Value& parentNode = *parentNodeRef;

	if (!parentNode.HasMember(ENTITY_NODE)) {
		return vector<Entity>();
	}

	Value& childNode = parentNode[ENTITY_NODE];
	if (!childNode.IsArray()) {
		return vector<Entity>();
	}

	vector<Entity> entities;
	entities.clear();
	for (SizeType i = 0; i < childNode.Size(); i++) {
		Value& entityNode = childNode[i];
		entities.push_back(ParseEntity(&entityNode));
	}
	return entities;
}

vector<Layer> Parser::ParseLayers(Value* parentNodeRef) {
	Value& parentNode = *parentNodeRef;

	if (!parentNode.HasMember(LAYER_NODE)) {
		return vector<Layer>();
	}

	Value& childNode = parentNode[LAYER_NODE];
	if (!childNode.IsArray()) {
		return vector<Layer>();
	}
	
	vector<Layer> layers;
	layers.clear();
	for (SizeType i = 0; i < childNode.Size(); i++) {
		Value* layerNode = &childNode[i];
		layers.push_back(ParseLayer(layerNode));
	}
	return layers;
}

Coordinate Parser::ParseCoordinate(Value* parentNodeRef) {
	Value& parentNode = *parentNodeRef;

	if (!parentNode.HasMember(COORDINATE_NODE)) {
		return Coordinate();
	}

	Value& childNode = parentNode[COORDINATE_NODE];
	if (!childNode.IsObject()) {
		return Coordinate();
	}

	int x;
	if (childNode.HasMember(COORDINATE_X_NODE) && childNode[COORDINATE_X_NODE].IsInt()) {
		x = childNode[COORDINATE_X_NODE].GetInt();
	}

	int y;
	if (childNode.HasMember(COORDINATE_Y_NODE) && childNode[COORDINATE_Y_NODE].IsInt()) {
		y = childNode[COORDINATE_Y_NODE].GetInt();
	}

	return Coordinate(x, y);
}

Entity Parser::ParseEntity(Value* parentNodeRef) {
	Value& parentNode = *parentNodeRef;

	if (!parentNode.IsObject()) {
		return Entity();
	}

	int id;
	if (parentNode.HasMember(ENTITY_ID_NODE) && parentNode[ENTITY_ID_NODE].IsInt()) {
		id = parentNode[ENTITY_ID_NODE].GetInt();
	}

	string type;
	if (parentNode.HasMember(ENTITY_TYPE_NODE) && parentNode[ENTITY_TYPE_NODE].IsString()) {
		type = parentNode[ENTITY_TYPE_NODE].GetString();
	}

	string color;
	if (parentNode.HasMember(ENTITY_COLOR_NODE) && parentNode[ENTITY_COLOR_NODE].IsString()) {
		color = parentNode[ENTITY_COLOR_NODE].GetString();
	}

	Dimensions dimensions = ParseDimensions(parentNodeRef);

	Coordinate coordinate = ParseCoordinate(parentNodeRef);
	
	string imagePath;
	if (parentNode.HasMember(ENTITY_IMAGE_PATH_NODE) && parentNode[ENTITY_IMAGE_PATH_NODE].IsString()) {
		imagePath = parentNode[ENTITY_IMAGE_PATH_NODE].GetString();
	}

	int zIndex;
	if (parentNode.HasMember(ENTITY_ZINDEX_NODE) && parentNode[ENTITY_ZINDEX_NODE].IsInt()) {
		zIndex = parentNode[ENTITY_ZINDEX_NODE].GetInt();
	}

	return Entity(id, type, color, dimensions, coordinate, imagePath, zIndex);
}

Layer Parser::ParseLayer(Value* parentNodeRef) {
	Value& parentNode = *parentNodeRef;
	
	if (!parentNode.IsObject()) {
		return Layer();
	}

	int id;
	if (parentNode.HasMember(LAYER_ID_NODE) && parentNode[LAYER_ID_NODE].IsInt()) {
		id = parentNode[LAYER_ID_NODE].GetInt();
	}

	int zIndex;
	if (parentNode.HasMember(LAYER_ZINDEX_NODE) && parentNode[LAYER_ZINDEX_NODE].IsInt()) {
		zIndex = parentNode[LAYER_ZINDEX_NODE].GetInt();
	}

	string imagePath;
	if (parentNode.HasMember(LAYER_IMAGE_PATH_NODE) && parentNode[LAYER_IMAGE_PATH_NODE].IsString()) {
		imagePath = parentNode[LAYER_IMAGE_PATH_NODE].GetString();
	}

	return Layer(id, zIndex, imagePath);
}

Window Parser::ParseWindow() {
	if (!document.HasMember(WINDOW_NODE)) {
		return Window();
	}

	Value* windowNode = &document[WINDOW_NODE];
	if (!windowNode->IsObject()) {
		return Window();
	}

	return Window(ParseDimensions(windowNode));
}

Configuration Parser::ParseConfiguration() {
	if (!document.HasMember(CONFIGURATION_NODE)) {
		return Configuration();
	}

	Value& confNode = document[CONFIGURATION_NODE];
	
	if (!confNode.IsObject()) {
		return Configuration();
	}

	int scrollSpeed;
	if (confNode.HasMember(CONFIGURATION_SCROLL_SPEED_NODE) && confNode[CONFIGURATION_SCROLL_SPEED_NODE].IsInt()) {
		scrollSpeed = confNode[CONFIGURATION_SCROLL_SPEED_NODE].GetInt();
	}

	return Configuration(scrollSpeed);
}

void Parser::ParseScenario(Scenario* scenario) {
	
	if (!document.HasMember(SCENARIO_NODE)) {
		return;
	}

	Value& scenarioNode = document[SCENARIO_NODE];
	if (!scenarioNode.IsObject()) {
		return;
	}

	Dimensions dimensions = ParseDimensions(&scenarioNode);
	scenario->SetDimensions(dimensions);
	
	vector<Layer> layers = ParseLayers(&scenarioNode);
	scenario->SetLayers(layers);
	
	vector<Entity> entities = ParseEntities(&scenarioNode);
	scenario->SetEntities(entities);

	return;
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

