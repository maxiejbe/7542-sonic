#include "Message.h"

const char* MESSAGE_TYPE_NODE = "t";
const char* MESSAGE_TIME_STEP_NODE = "dt";
const char* MESSAGE_KEY_PRESSED_LEFT_NODE = "klp";
const char* MESSAGE_KEY_PRESSED_SPACE_NODE = "ksp";
const char* MESSAGE_KEY_PRESSED_RIGHT_NODE = "krp";
const char* MESSAGE_KEY_PRESSED_UP_NODE = "kup";
const char* MESSAGE_KEY_UNPRESSED_LEFT_NODE = "klu";
const char* MESSAGE_KEY_UNPRESSED_RIGHT_NODE = "kru";
const char* MESSAGE_KEY_UNPRESSED_SPACE_NODE = "ksu";
const char* MESSAGE_USERNAME_NODE = "un";
const char* MESSAGE_TEAMID_NODE = "tid";

const int MESSAGE_DEFAULT_TEAMID = -1;

Message::Message()
{
	this->userName = string();
	this->teamId = MESSAGE_DEFAULT_TEAMID;
}

Message::Message(double dt, bool isKPLeft, bool isKPSpace, bool isKPRight, bool isKPUp, bool isKULeft, bool isKURight, bool isKUSpace)
{
	this->dt = dt;
	this->isKPLeft = isKPLeft;
	this->isKPSpace = isKPSpace;
	this->isKPRight = isKPRight;
	this->isKPUp = isKPUp;
	this->isKULeft = isKULeft;
	this->isKURight = isKURight;
	this->isKUSpace = isKUSpace;
}

void Message::setType(MessageType type)
{
	this->type = type;
}

MessageType Message::getType()
{
	return this->type;
}

double Message::getTimeStep()
{
	return this->dt;
}

bool Message::getIsKPLeft()
{
	return this->isKPLeft;
}

bool Message::getIsKPSpace()
{
	return this->isKPSpace;
}

bool Message::getIsKPRight()
{
	return this->isKPRight;
}

bool Message::getIsKPUp()
{
	return this->isKPUp;
}

bool Message::getIsKULeft()
{
	return this->isKULeft;
}

bool Message::getIsKURight()
{
	return this->isKURight;
}

bool Message::getIsKUSpace()
{
	return this->isKUSpace;
}

void Message::setUserName(string userName)
{
	this->userName = userName;
}

void Message::setTeamId(int teamId)
{
	this->teamId = teamId;
}

string Message::getUserName()
{
	return this->userName;
}

int Message::getTeamId()
{
	return this->teamId;
}

/*Serializable*/


bool Message::equals(Message & message)
{
	if (this->isKPUp != message.getIsKPUp()) return false;
	if (this->isKPLeft != message.getIsKPLeft()) return false;
	if (this->isKPRight != message.getIsKPRight()) return false;
	if (this->isKPSpace != message.getIsKPSpace()) return false;
	if (this->isKULeft != message.getIsKULeft()) return false;
	if (this->isKURight != message.getIsKURight()) return false;
	if (this->isKUSpace != message.getIsKUSpace()) return false;
	
	return true;
}

void Message::unserialize(Value * nodeRef)
{
	parseInt((int*)&type, no_type, nodeRef, MESSAGE_TYPE_NODE, Validator::intGreaterThanOrEqualToZero);

	switch (this->type)
	{
		case status:
			//Time step
			parseDouble(&dt, 0, nodeRef, MESSAGE_TIME_STEP_NODE);
			//keys
			parseBool(&isKPLeft, false, nodeRef, MESSAGE_KEY_PRESSED_LEFT_NODE);
			parseBool(&isKPRight, false, nodeRef, MESSAGE_KEY_PRESSED_RIGHT_NODE);
			parseBool(&isKPSpace, false, nodeRef, MESSAGE_KEY_PRESSED_SPACE_NODE);
			parseBool(&isKPUp, false, nodeRef, MESSAGE_KEY_PRESSED_UP_NODE);
			parseBool(&isKULeft, false, nodeRef, MESSAGE_KEY_UNPRESSED_LEFT_NODE);
			parseBool(&isKURight, false, nodeRef, MESSAGE_KEY_UNPRESSED_RIGHT_NODE);
			parseBool(&isKUSpace, false, nodeRef, MESSAGE_KEY_UNPRESSED_SPACE_NODE);
			break;
		case username:
			parseString(&userName, "", nodeRef, MESSAGE_USERNAME_NODE);
			parseInt(&teamId, MESSAGE_DEFAULT_TEAMID, nodeRef, MESSAGE_TEAMID_NODE, Validator::intGreaterThanOrEqualToZero);
			break;
		default:
			break;
	}
}

char * Message::getNodeName()
{
	return nullptr;
}

string Message::serialize()
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);
	performSerialization(writer);
	return s.GetString();
}

void Message::performSerialization(Writer<StringBuffer>& writer) {
	writer.StartObject();
	
	writer.String(MESSAGE_TYPE_NODE);
	writer.Int(this->type);
	
	//player number
	switch (this->type)
	{
		case status:
			writer.String(MESSAGE_TIME_STEP_NODE);
			writer.Double(this->dt);
			writer.String(MESSAGE_KEY_PRESSED_LEFT_NODE);
			writer.Bool(this->isKPLeft);
			writer.String(MESSAGE_KEY_PRESSED_SPACE_NODE);
			writer.Bool(this->isKPSpace);
			writer.String(MESSAGE_KEY_PRESSED_RIGHT_NODE);
			writer.Bool(this->isKPRight);
			writer.String(MESSAGE_KEY_PRESSED_UP_NODE);
			writer.Bool(this->isKPUp);
			writer.String(MESSAGE_KEY_UNPRESSED_LEFT_NODE);
			writer.Bool(this->isKULeft);
			writer.String(MESSAGE_KEY_UNPRESSED_RIGHT_NODE);
			writer.Bool(this->isKURight);
			writer.String(MESSAGE_KEY_UNPRESSED_SPACE_NODE);
			writer.Bool(this->isKUSpace);
		case username:
			writer.String(MESSAGE_USERNAME_NODE);
			writer.String(this->userName.c_str());
			writer.String(MESSAGE_TEAMID_NODE);
			writer.Int(this->teamId);
			break;
		default:
			break;
	}
	writer.EndObject();
}
