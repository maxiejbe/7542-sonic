#ifndef I_Serializable_H
#define I_Serializable_H

#include "rapidjson/document.h"

using namespace rapidjson;

template<class T>
class ISerializable {
public:
	T Unserialize(Value value);
};

#endif