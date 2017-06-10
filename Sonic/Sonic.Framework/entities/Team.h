#ifndef TEAM_H
#define TEAM_H

#include <string>
#include "common/Serializable.h"
#include "common/Validator.h"

using namespace std;

class Team: public Serializable
{
public:
	Team();
	Team(int, string);
	~Team();

	int getId();
	string getName();

	// Inherited via Serializable
	void unserialize(Value* nodeRef) override;
	char* getNodeName() override;
	string serialize() override;

private:
	int id;
	string name;
};

#endif

