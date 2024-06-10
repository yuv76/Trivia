#pragma once
#include "Game.h"
#include "SqliteDatabase.h"
#include "Room.h"

class GameManager
{
private:
	IDatabase* m_database;
	std::map<int, Game> m_games;

	int getNextAvailableId();

public:
	GameManager(IDatabase* DB);
	int createGame(Room& r);
	void deleteGame(int gameId);//might not be void
	Game& getGameByID(int id);
};