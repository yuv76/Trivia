#include "LoggedUser.h"

/*
C'tor to a logged user.
in: a username name string.
*/
LoggedUser::LoggedUser(std::string username)
{
	this->m_username = username; 
}

/*
gets the username of the logged user.
in: none.
out: the user's name
*/
std::string LoggedUser::getUsername() const
{ 
	return this->m_username; 
}

/*
the == operator for a logged user, compares current user to another given one.
in: the other logged user to compare to.
out: true if the users are the same (same username), false otherwise.
*/
bool LoggedUser::operator==(const LoggedUser& l) const
{
	return this->m_username == l.getUsername();
}

/*
the < operator for a logged user, compares current user to another given one.
in: the other logged user to compare to.
out: true if this user's name is smaller compared to the other one, false otherwise.
*/
bool LoggedUser::operator<(const LoggedUser& l) const
{
	return this->m_username < l.m_username;
}