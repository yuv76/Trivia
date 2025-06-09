#pragma once

#include <string>

class LoggedUser
{
public:
	LoggedUser() { m_username = ""; }
	LoggedUser(std::string username);
	std::string getUsername() const;
	bool operator==(const LoggedUser& l) const;
	bool operator<(const LoggedUser& l) const;

private: 
	std::string m_username;
};
