#pragma once

#include "IDatabase.h"
#include <map>
#include <mutex>

class StatisticsManager
{
private:
	IDatabase* m_database;

	std::mutex _mtx;
	std::unique_lock<std::mutex> _lck;

public:
	StatisticsManager(IDatabase* db);
	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(std::string username);
};