#include "StatisticsManager.h"

/*

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

	int topUser = -1;
	int currentMax = -1;
	for (auto entry : score) {
		if (entry.second < currentMax) {
			continue;
		}

		//topUser = entry.first;
		//currentMax = entry.second;
	}

	
	return s;
}

/*

*/
std::vector<std::string> StatisticsManager::getUserStatistics(std::string username)
{
	std::vector<std::string> s;

	int correct = m_database->getNumOfCorrectAnswers(username);
	int total = m_database->getNumOfTotalAnswers(username);

	s.push_back(username);
	s.push_back(std::to_string(correct));
	s.push_back(std::to_string(total));

	return s;
}
