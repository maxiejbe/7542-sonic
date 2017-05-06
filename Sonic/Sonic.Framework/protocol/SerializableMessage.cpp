#include "SerializableMessage.h"

SerializableMessage::SerializableMessage()
{
}

bool SerializableMessage::fromJson(string json)
{
	Document document;
	const char* message = StringUtils::convert(json);
	if (document.Parse(message).HasParseError()) {
		LOG(logERROR) << "No se pudo deserializar el mensaje: " << json;
		return false;
	}

	unserialize(&document);
	return true;
}

