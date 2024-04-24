#pragma once
#include <vector>
#include "SqliteDatabase.h"
#include "LoggedUser.h"

class LoginManager
{
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
public:
	LoginManager();
	~LoginManager();
	bool signup(std::string username, std::string password, std::string email);
	int login(std::string username, std::string password);
	bool logout(std::string username);
};