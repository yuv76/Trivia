#pragma once
#include <string>

struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	double timePerQuestion;
	unsigned int isActive;
};