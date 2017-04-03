#ifndef I_SERIALIZABLE_H
#define I_SERIALIZABLE_H

#include "rapidjson/document.h"
#include <vector>
#include <string>
#include "../../Logger.h"

using namespace rapidjson;
using namespace std;

class Serializable {
public:
	//TODO: Change name to parse inner object
	void ParseObject(Value* parentNodeRef);

	template <class T>
	void ParseCollection(vector<T>* collection, Value* parentNodeRef, char* collectionNodeName);

	void ParseCurrentObject(Value* nodeRef);

	void ParseInt(int* value, int defaultValue, Value* nodeRef, const char* fieldName);
	void ParseString(string* value, string defaultValue, Value* nodeRef, const char* fieldName);

	virtual void Unserialize(Value* nodeRef) = 0;
	virtual char* GetNodeName() = 0;
private:
	const char* MESSAGE_PARSING_NODE_COLLECTION = "Iterando colecci�n: ";
	const char* MESSAGE_NOT_FOUND_NODE_COLLECTION = "La colecci�n no se encuentra en el nodo: ";
	const char* MESSAGE_NOT_ARRAY_NODE_COLLECTION = "La colecci�n no es un arreglo de objetos: ";

	const char* MESSAGE_ITERATING_OBJECT_NODE_COLLECTION = "Iterando objeto de la colecci�n n�mero ";
	const char* MESSAGE_END_PARSING_NODE_COLLECTION = "Finaliz� la iteraci�n.";
};

template <class T>
inline void Serializable::ParseCollection(vector<T>* collection, Value* parentNodeRef, char * collectionNodeName)
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
		entity.ParseCurrentObject(&entityNode);
		collection->push_back(entity);
	}

	LOG(logINFO) << MESSAGE_END_PARSING_NODE_COLLECTION;
}

#endif

