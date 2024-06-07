#pragma once

#include "GameData.h"
#include "LoggedUser.h"
#include "SqliteDatabase.h"
#include <map>
#include <ctime>

class Game
{
private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	int m_gameId;
	double m_answerTimeout;
	bool _isActive;

	void sumitGameStatsToDB(IDatabase* DB); // return type made to have one, but not official and could change.

public:
	Game(std::vector<Question> questions, std::vector<LoggedUser> users, int id, double ansTime);
	Question getQuestionForUser(LoggedUser user); // return and parameter types made to have one, but not official and could change.
	void submitAnswer(int answerId, LoggedUser user, double ansTime); // return type made to have one, but not official and could change.
	void removePlayer(LoggedUser user); // return type made to have one, but not official and could change.
	int getId();
	void endGame();
};
