#include "LoginManager.h"

/*
C'tor for LoginManager.
in: a pointer to the database.
*/
LoginManager::LoginManager(IDatabase* db):
	m_database(db)
{
	m_database->open();
}

/*
D'tor for LoginManager.
in: none.
*/
LoginManager::~LoginManager()
{
	this->m_database->close();
	delete this->m_database;
}

/*
signs a new user to the database (if name is not taken).
in: username, password and email of the new user.
out: true if logged sucessfully, false otherwise.
*/
bool LoginManager::signup(std::string username, std::string password, std::string email)
{
	int res = this->m_database->addNewUser(username, password, email);
	if (res == USER_NOT_ADDED)
	{
		return false;
	}
	LoggedUser l = LoggedUser(username);
	this->m_loggedUsers.push_back(l);
	return true;
}

/*
checks if username and password are correct and if they are adds user to users list.
in: username and its presumable password.
out: 1 if logged sucessfuly, -1 if user dosnt exist, 0 otherwise.
*/
int LoginManager::login(std::string username, std::string password)
{
	int res = this->m_database->doesPasswordMatch(username, password);
	if (res == PASSWORDS_MATCH)
	{
		//add user to logged users list.
		LoggedUser l = LoggedUser(username);
		this->m_loggedUsers.push_back(l);
	}
	return res;
}

/*
removes user from list of logged users.
in: username to log out.
out: true if logged out sucessfully, false if user wasnt logged in in the first place.
*/
bool LoginManager::logout(std::string username)
{
	bool removed = false;
	auto i = this->m_loggedUsers.begin();
	for (i; i != this->m_loggedUsers.end(); ++i)
	{
		if (i->getUsername() == username)
		{
			//remove the user.
			this->m_loggedUsers.erase(i);
			removed = true;
			//exit loop.
			break;
		}
	}
	return removed;
}