#pragma once
#include "GameData.h"
#include "LoggedUser.h"
#include <map>

class GameManager
{
private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
	int m_gameId;

	void sumitGameStatsToDB(GameData); // return type made to have one, but not official and could change.

public:
	Question getQuestionForUser(LoggedUser user); // return and parameter types made to have one, but not official and could change.
	void submitAnswer(); // return type made to have one, but not official and could change.
	void removePlayer(); // return type made to have one, but not official and could change.
};