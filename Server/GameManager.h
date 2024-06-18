#pragma once
#include "Game.h"
#include "SqliteDatabase.h"
#include "Room.h"

#include <mutex>

class GameManager
{
private:
	IDatabase* m_database;
	std::map<int, Game> m_games;

	std::mutex _mtx;
	std::unique_lock<std::mutex> _lck;

	int getNextAvailableId();

public:
	GameManager(IDatabase* DB);
	int createGame(Room& r);
	void deleteGame(int gameId);//might not be void
	Game& getGameByID(int id);
};