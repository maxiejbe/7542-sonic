#ifndef I_SERIALIZABLE_H
#define I_SERIALIZABLE_H

#include <document.h>
#include <vector>
#include <string>
#include "../../Logger.h"
#include <functional>
#include <cstdio>
#include <prettywriter.h>

using namespace rapidjson;
using namespace std;

class Serializable {
public:
	void parseObject(Value* parentNodeRef);

	template <class T>
	void parseCollection(vector<T>* collection, Value* parentNodeRef, char* collectionNodeName);

	void parseCurrentObject(Value* nodeRef);

	void parseInt(int * value, int defaultValue, Value * nodeRef, const char* fieldName, function<bool(int)> condition = nullptr);
	void parseString(string* value, string defaultValue, Value* nodeRef, const char* fieldName);
	void parseDouble(double* value, double defaultValue, Value* nodeRef, const char* fieldName);
	void parseBool(bool* value, bool defaultValue, Value* nodeRef, const char* fieldName);

	string getNodeContent(Value* nodeRef);

	virtual void unserialize(Value* nodeRef) = 0;
	virtual char* getNodeName() = 0;
	virtual string serialize();
private:
	const char* MESSAGE_PARSING_NODE_COLLECTION = "Iterando colecci�n: ";
	const char* MESSAGE_NOT_FOUND_NODE_COLLECTION = "La siguiente colecci�n no se encuentra: ";
	const char* MESSAGE_NOT_ARRAY_NODE_COLLECTION = "La siguiente colecci�n no es un arreglo de objetos: ";

	const char* MESSAGE_ITERATING_OBJECT_NODE_COLLECTION = "Iterando objeto de la colecci�n n�mero ";
	const char* MESSAGE_END_PARSING_NODE_COLLECTION = "Finaliz� la iteraci�n.";
};

template <class T>
inline void Serializable::parseCollection(vector<T>* collection, Value* parentNodeRef, char * collectionNodeName)
{
	Value& parentNode = *parentNodeRef;
	if (!parentNode.HasMember(collectionNodeName)) {
		LOG(logWARNING) << MESSAGE_NOT_FOUND_NODE_COLLECTION << collectionNodeName;
		return;
	}

	Value& entitiesNode = parentNode[collectionNodeName];

	collection->clear();

	if (!entitiesNode.IsArray()) {
		LOG(logWARNING) << MESSAGE_NOT_ARRAY_NODE_COLLECTION << collectionNodeName;
	}
	
	LOG(logINFO) << MESSAGE_PARSING_NODE_COLLECTION << collectionNodeName;

	//Iterate collection
	for (SizeType i = 0; i < entitiesNode.Size(); i++) {
		LOG(logINFO) << MESSAGE_ITERATING_OBJECT_NODE_COLLECTION << to_string(i);
		Value& entityNode = entitiesNode[i];
		T entity;
		entity.parseCurrentObject(&entityNode);
		collection->push_back(entity);
	}

	LOG(logINFO) << MESSAGE_END_PARSING_NODE_COLLECTION;
}

#endif


