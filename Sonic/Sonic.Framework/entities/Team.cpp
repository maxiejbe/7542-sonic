#include "Team.h"

const char* TEAM_ID = "id";
const char* TEAM_NAME = "n";

const int TEAM_DEFAULT_ID = -1;

Team::Team()
{
	this->id = TEAM_DEFAULT_ID;
	this->name = string();
}

Team::Team(int id, string name)
{
	this->id = id;
	this->name = name;
}

Team::~Team()
{
}

int Team::getId()
{
	return this->id;
}

string Team::getName()
{
	return this->name;
}

void Team::unserialize(Value * nodeRef)
{
	//id
	parseInt(&id, 0, nodeRef, TEAM_ID, Validator::intGreaterThanOrEqualToZero);
	//name
	parseString(&name, "", nodeRef, TEAM_NAME);

}

char * Team::getNodeName()
{
	return nullptr;
}

string Team::serialize()
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);

	writer.StartObject();
	writer.String(TEAM_ID);
	writer.Int(this->id);
	writer.String(TEAM_NAME);
	writer.String(this->name.c_str());

	writer.EndObject();
	return s.GetString();
}
