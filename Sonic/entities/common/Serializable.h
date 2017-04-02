#ifndef I_SERIALIZABLE_H
#define I_SERIALIZABLE_H

#include "rapidjson/document.h"
#include <vector>

using namespace rapidjson;
using namespace std;

class Serializable {
public:
	//TODO: Change name to parse inner object
	void ParseObject(Value* parentNodeRef);

	template <class T>
	void ParseCollection(vector<T>* collection, Value* nodeRef, char* collectionNodeName);

	void ParseCurrentObject(Value* nodeRef);

	virtual void Unserialize(Value* nodeRef) = 0;
	virtual char* GetNodeName() = 0;
};

template <class T>
inline void Serializable::ParseCollection(vector<T>* collection, Value* nodeRef, char * collectionNodeName)
{
	Value& node = *nodeRef;
	Value& entitiesNode = node[collectionNodeName];

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


