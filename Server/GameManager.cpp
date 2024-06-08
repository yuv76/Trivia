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
Game& GameManager::createGame(Room r)
{
	double ansTimeout = r.getRoomData().timePerQuestion;
	std::vector<LoggedUser> users = r.getUsers();
	int id = this->getNextAvailableId();

	std::vector<Question> questions;
	std::vector<QuestionData> Qdata = this->m_database->getQuestions(r.getRoomData().numOfQuestionsInGame);
	auto i = Qdata.begin();
	for (i; i != Qdata.end(); i++)
	{
		questions.push_back(Question(i->question, i->wrongAnswer1, i->wrongAnswer2, i->wrongAnswer3, i->rightAnswer, i->id));
	}

	Game game(questions, users, id, ansTimeout);

	return game;
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
		if (i->getId() == gameId)
		{
			i->endGame();
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
		id = this->m_games.back().getId();
		//increase id by one to get the next unused id.
		id++;
	}
	return id;
}
