#pragma once
#include <string>

class LoggedUser
{
public:
	LoggedUser(std::string username) { this->m_username = username; }
	std::string getUsername() { return this->m_username; }

private: 
	std::string m_username;
};