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
		delete message;
		return false;
	}

	delete message;
	unserialize(&document);
	return true;
}

