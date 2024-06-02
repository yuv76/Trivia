#pragma once

#include "IDatabase.h"
#include <map>

class StatisticsManager
{
private:
	IDatabase* m_database;
public:
	StatisticsManager(IDatabase* db);
	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(std::string username);
};