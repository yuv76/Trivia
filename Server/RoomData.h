#pragma once

#include "LoggedUser.h"
#include <string>

struct RoomData
{
	unsigned int id;
	std::string name;
	std::string owner;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	double timePerQuestion;
	unsigned int isActive;
};