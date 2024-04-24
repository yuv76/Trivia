#pragma once
#include <string>

class LoggedUser
{
public:
	std::string getUsername() { return this->m_username; }

private: 
	std::string m_username;
};