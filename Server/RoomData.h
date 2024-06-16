#pragma once

#include "LoggedUser.h"
#include <string>

#define ROOM_CLOSED 0
#define ROOM_LOBY_STATE 1
#define GAME_STARTED_IN_ROOM 2

struct RoomData
{
	unsigned int id;
	std::string name;
	std::string owner;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
};