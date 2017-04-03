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
};

template <class T>
inline void Serializable::ParseCollection(vector<T>* collection, Value* parentNodeRef, char * collectionNodeName)
{
	Value& parentNode = *parentNodeRef;
	Value& entitiesNode = parentNode[collectionNodeName];

	collection->clear();

	if (entitiesNode.IsArray()) {
		for (SizeType i = 0; i < entitiesNode.Size(); i++) {
			Value& entityNode = entitiesNode[i];
			T entity;
			entity.ParseCurrentObject(&entityNode);
			collection->push_back(entity);
		}
	}
}

#endif


