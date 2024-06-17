#include "GameManager.h"

/*
C'tor for game manager.
in: database pointer.
*/
GameManager::GameManager(IDatabase* DB):
	m_database(DB)
{}

/*
create a game that takes place in a room.
in: the room to crete the game in.
out: the newly created game object;
*/
int GameManager::createGame(Room& r)
{
	double ansTimeout = r.getRoomData().timePerQuestion;
	std::vector<LoggedUser> users = r.getUsers();
	int id = this->getNextAvailableId();

	std::vector<Question> questions;
	std::vector<QuestionData> Qdata = this->m_database->getQuestions(r.getRoomData().numOfQuestionsInGame);


	Game game(Qdata, users, id, ansTimeout);
	this->m_games.insert(std::make_pair(id, game));

	return id;
}

/*
deletes a game from the manager.
in: the game to delete's id.
out: none.
*/
void GameManager::deleteGame(int gameId)
{
	auto i = this->m_games.begin();
	for (i; i != this->m_games.end(); i++)
	{
		if (i->first == gameId)
		{
			i->second.endGame(this->m_database);
		}
	}
}

/*
gets the next available game id that is not yet used.
in: none.
out: the id, int.
*/
int GameManager::getNextAvailableId()
{
	int id = 0;
	if (this->m_games.empty())
	{
		//first Game.
		id = 1;
	}
	else
	{
		//the map is sorted by increased oredr, so its last position will be its biggest key.
		id = this->m_games.rbegin()->first;
		//increase id by one to get the next unused id.
		id++;
	}
	return id;
}

/*
gets a game from the manager by its id.
in: the game's id.
out: the game's reference.
*/
Game& GameManager::getGameByID(int id)
{
	if (this->m_games.find(id) != this->m_games.end()) // if key exists.
	{
		return this->m_games.find(id)->second;
	}
	//else
	throw std::exception("Invalid Room ID.");
}
