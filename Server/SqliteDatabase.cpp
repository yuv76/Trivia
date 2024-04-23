#include "SqliteDatabase.h"

/*
opens a database file. if not exists creates it.
in: none.
out: true upon sucess.
*/
bool SqliteDatabase::open()
{

	int fileExist = _access(DATABASE_FILE_NAME, 0);

	int res = sqlite3_open(DATABASE_FILE_NAME, &this->database);
	if (res != SQLITE_OK)
	{
		this->database = nullptr;
		throw std::exception("Failed to open Database");
	}
	if (fileExist == FILE_DOES_NOT_EXIST) //else (if already exists), do nothing.
	{
		const char* createUsersTableSQL = "CREATE TABLE IF NOT EXISTS USERS (USERNAME TEXT PRIMARY KEY NOT NULL , PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL);";

		char* errMessage[100];
		//create users table
		res = sqlite3_exec(this->database, createUsersTableSQL, nullptr, nullptr, errMessage);
		if (res != SQLITE_OK)
		{
			throw std::exception(*errMessage);
		}
	}

	return true;
}

/*
closes the database.
in: none.
out: true upon sucess.
*/
bool SqliteDatabase::close()
{
	sqlite3_close(this->database);
	this->database = nullptr;
	return true;
}

/*
checks if a user was found.
in: the data(int pointer), number of fields in column, the field contents, the field names.
out: 0 upon sucess.
*/
int SqliteDatabase::callbackCheckExistance(void* data, int argc, char** argv, char** azColName)
{
	int* exists = static_cast<int*>(data);
	if (argc != 0)
	{
		*exists = USER_EXIST;
	}
	else
	{
		*exists = USER_DONT_EXIST;
	}
	return 0;
}

/*
checks if a user with a given name exists within the database.
in: the username to look for.
out: 1 if exists, 0 otherwise.
*/
int SqliteDatabase::doesUserExist(std::string username)
{
	char* errMessage[100];
	int exists = 0;
	std::string getUserSQL = "select * from users WHERE USERNAME == \"" + username + "\";";
	int res = sqlite3_exec(this->database, getUserSQL.c_str(), callbackCheckExistance, &exists, errMessage);
	if (res != SQLITE_OK)
	{
		throw std::exception(*errMessage);
	}
	return exists;
}

/*
checks if user with a given name has given password (if the password is the user's password).
int: the user's name, the password to check.
out: 1 if match, 0 otherwise.
*/
int SqliteDatabase::doesPasswordMatch(std::string username, std::string password)
{
	char* errMessage[100];
	int match = 0;

	if (this->doesUserExist(username) == USER_DONT_EXIST)
	{
		match = PASSWORDS_DONT_MATCH;
	}
	else
	{
		std::string matchPasswordSQL = "select * from users WHERE USERNAME == \"" + username + "\" and PASSWORD == \"" + password + "\"; ";
		int res = sqlite3_exec(this->database, matchPasswordSQL.c_str(), callbackCheckExistance, &match, errMessage);
		if (res != SQLITE_OK)
		{
			throw std::exception(*errMessage);
		}
	}
	
	return match;
}

/*
adds a new user to the database.
in: username, password and email of the new user.
out: 1 if added sucessfully.
*/
int SqliteDatabase::addNewUser(std::string username, std::string password, std::string email)
{
	//check if user with given name already exists.
	if (this->doesUserExist(username) == USER_EXIST)
	{
		return USER_NOT_ADDED;
	}
	//if not already exists, add it.
	char* errMessage[100];
	std::string addUserSQL = "";
	addUserSQL = "INSERT INTO users VALUES(\"" + username + "\", \"" + password + "\", \"" + email + "\"); ";
	int res = sqlite3_exec(this->database, addUserSQL.c_str(), nullptr, nullptr, errMessage);
	if (res != SQLITE_OK)
	{
		throw std::exception(*errMessage);
	}
	return USER_ADDED;
}