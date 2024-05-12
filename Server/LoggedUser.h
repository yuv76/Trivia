#pragma once

#include <string>

class LoggedUser
{
public:
	LoggedUser(std::string username);
	std::string getUsername();
	bool operator==(LoggedUser& l);


private: 
	std::string m_username;
};
