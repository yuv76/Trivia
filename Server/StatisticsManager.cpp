#include "StatisticsManager.h"

/*
C'tor for statistics manager.
in: pointer to the database object.
*/
StatisticsManager::StatisticsManager(IDatabase* db):
	m_database(db)
{}

/*
gets the top 5 users.
in: none.
out: a vector of the top five users user names.
*/
std::vector<std::string> StatisticsManager::getHighScore()
{
	std::vector<std::string> s;

	std::vector<std::string> temp;
	std::vector<std::string> users = m_database->getUsers();
	std::map<std::string, int> score;
	int userscore;

	for (const auto& user : users)
	{
		temp = this->getUserStatistics(user);
		userscore = stoi(temp[1]);
		score[user] = userscore;
	}

	for (int i = 0; i < 5; i++)// add the best 5 times.
	{
		std::string topUser = "no_user";
		int currentMax = -1;

		for (auto entry : score)
		{
			if (entry.second < currentMax)
			{
				continue;
			}

			topUser = entry.first;
			currentMax = entry.second;
		}
		s.push_back(topUser);// push it into the vector in order.
		score.erase(topUser);// remove it from the original scores vector.

	}

	return s;
}

/*
gets the user's statistics from the db.
in: the user's username.
out: a vector with the user's states.
*/
std::vector<std::string> StatisticsManager::getUserStatistics(std::string username)
{
	std::vector<std::string> s;

	int correct = m_database->getNumOfCorrectAnswers(username);
	int total = m_database->getNumOfTotalAnswers(username);
	int games = m_database->getNumOfPlayerGames(username);
	float average = m_database->getPlayerAverageAnswerTime(username);

	s.push_back(username);
	s.push_back(std::to_string(correct));
	s.push_back(std::to_string(total));
	s.push_back(std::to_string(games));
	s.push_back(std::to_string(average));

	return s;
}
