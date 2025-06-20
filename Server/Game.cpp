#include "Game.h"

/*
C'tor for game object.
in: questions for game in a vector, users in a vector, room's id, time for answer in the game.
*/
Game::Game(std::vector<QuestionData> questionDatas, std::vector<LoggedUser> users, int id, double ansTime, std::string admin, int roomId):
	m_gameId(id), m_answerTimeout(ansTime), _isActive(true), _submitted(false), _adminUsername(admin), _roomId(roomId)
{
	Question padding;
	padding.setStartQuestion();
	m_questions.push_back(padding);
	auto q = questionDatas.begin();
	for (q; q != questionDatas.end(); q++)
	{
		m_questions.push_back(Question(q->question, q->wrongAnswer1, q->wrongAnswer2, q->wrongAnswer3, q->rightAnswer, q->id));
	}

	//add players and create game data to each in a map.
	auto i = users.begin();
	for (i; i != users.end(); i++)
	{
		GameData tempGD;
		tempGD.averangeAnswerTime = 1; //init with something that wont affect the average when first submit will be entered.
		tempGD.correctAnswerCount = 0;
		tempGD.wrongAnswerCount = 0;
		tempGD.isActive = true;
		tempGD.currentQuestion = this->m_questions[0]; // first question.

		this->m_players[*i] = tempGD;
	}
	
}

/*
gets the next question for a given user.
in: the user, as a logged user object.
out: the question.
*/
Question Game::getQuestionForUser(LoggedUser user)
{
	bool found = false;
	int currId = this->m_players[user].currentQuestion.getQuestionId();
	Question nextQ;

	//get the question after the current one
	auto i = this->m_questions.begin();
	for (i; i != this->m_questions.end() && !found; i++)
	{
		if (i->getQuestionId() == currId)
		{
			found = true;
			//i++; //increase to get next one.
		}
	}
	if (i == this->m_questions.end())
	{
		nextQ.setEndQuestion();
	}
	else
	{
		nextQ = *i;
		this->m_players[user].currentQuestion = *i;
	}
	return nextQ;
}

/*
deals with user's answer, updates the data according to if it is right ro wrong.
in: the user's answer id, the user.
out: the correct answer's index.
*/
int Game::submitAnswer(int answerId, LoggedUser user, double ansTime)
{
	//update average.
	if (this->m_players[user].isActive)
	{
		int totalAnswered = this->m_players[user].correctAnswerCount + this->m_players[user].wrongAnswerCount;
		double oldAvg = this->m_players[user].averangeAnswerTime;
		double newAvg = oldAvg * totalAnswered;
		newAvg += ansTime;
		newAvg /= (totalAnswered + 1);
		this->m_players[user].averangeAnswerTime = newAvg;

		if (answerId == this->m_players[user].currentQuestion.getCorrectAnswerId())
		{
			// right answer
			this->m_players[user].correctAnswerCount++;
		}
		else
		{
			//wrong answer
			this->m_players[user].wrongAnswerCount++;
		}
		return this->m_players[user].currentQuestion.getCorrectAnswerId();
	}
	//if not active, shouldnt do anything.
	return -1;
}

/*
removes a user from being active in the game.
in: the user to remove.
out: none.
*/
void Game::removePlayer(LoggedUser user)
{
	this->m_players[user].isActive = false;
}

/*
updates the game's results in the database.
in: the database pointer.
out: none.
*/
void Game::sumitGameStatsToDB(IDatabase* db)
{
	auto i = this->m_players.begin();
	if (!_submitted)
	{
		for (i; i != this->m_players.end(); i++)
		{
			db->submitGameStatistics(i->second, i->first.getUsername());
		}
		_submitted = true;
	}
}

/*
gets the game's id.
in: none,
out: the id.
*/
int Game::getId()
{
	return this->m_gameId;
}

/*
makes the game state not active.
in: none.
out: none.
*/
void Game::endGame(IDatabase* db)
{
	this->_isActive = false;
	this->sumitGameStatsToDB(db);
}

/*
gets the game's users data.
in: none,
out: a vector with all of the gamedatas.
*/
std::vector<std::pair<LoggedUser, GameData>> Game::getData()
{
	std::vector<std::pair<LoggedUser,GameData>> sendData;
	std::pair<LoggedUser, GameData> temp;
	//GameData temp;
	std::string name;

	auto i = this->m_players.begin();
	for (i; i != this->m_players.end(); i++)
	{
		temp.second.averangeAnswerTime = i->second.averangeAnswerTime;
		temp.second.correctAnswerCount = i->second.correctAnswerCount;
		temp.second.currentQuestion = i->second.currentQuestion;
		temp.second.isActive = i->second.isActive;
		temp.second.wrongAnswerCount = i->second.wrongAnswerCount;
		temp.first = i->first;
		sendData.push_back(temp);
	}
	return sendData;
}

/*
gets the game's active state.
in: none.
out: true if active, false otherwise.
*/
bool Game::isActive()
{
	return this->_isActive;
}

/*
sets given user's status to a new one.
in: the new status to update to, the user to update in the game (the user is already in the game).
out: none.
*/
void Game::setUserStatus(bool newStatus, LoggedUser user)
{
	this->m_players[user].isActive = newStatus;
}

/*
gets given user's status in the game.
in: the user.
out: the boolean status.
*/
bool Game::getUserStatus(LoggedUser user)
{
	return this->m_players[user].isActive;
}

/*
checks if the game is still on, updates its active status according.
in: none.
out: none.
*/
void Game::checkIfFinished()
{
	bool gameFinished = true;

	auto i = this->m_players.begin();
	for (i; i != this->m_players.end() && gameFinished; i++)
	{
		if (i->second.isActive)
		{
			gameFinished = false;
		}
	}

	this->_isActive = !gameFinished;//if game not finished, active is true.
}

/*
getter for game admin's username.
in: none.
out: the username.
*/
std::string Game::getAdminUsername()
{
	return this->_adminUsername;
}

/*
gets the room the game is in's id.
in: none.
out: the id.
*/
int Game::getRoomId()
{
	return this->_roomId;
}