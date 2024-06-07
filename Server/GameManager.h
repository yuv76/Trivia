#pragma once
#include "Game.h"
#include "SqliteDatabase.h"
#include "Room.h"

class GameManager
{
private:
	IDatabase* m_database;
	std::vector<Game> m_games;

	int getNextAvailableId();

public:
	GameManager(IDatabase* DB);
	Game& createGame(Room r);
	void deleteGame(int gameId);//might not be void
};