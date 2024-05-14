#pragma once

#include "sqlite3.h"
#include "io.h"
#include "IDatabase.h"

#include "Requests.h"
#include <vector>
#include <string>

#define MSG_HEADER 1

#define DATABASE_FILE_NAME "SqliteDatabase.db"

#define FILE_DOES_NOT_EXIST -1

#define USER_DONT_EXIST 0
#define USER_EXIST 1

#define PASSWORDS_DONT_MATCH 0
#define PASSWORDS_MATCH 1
#define USER_NOT_EXIST 2

#define USER_ADDED 1
#define USER_NOT_ADDED 0

#define QUESTIONS_ADDED 1


class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase() = default;
	virtual ~SqliteDatabase() = default;

	virtual bool open();
	virtual bool close();
	virtual int doesUserExist(std::string username);
	virtual int doesPasswordMatch(std::string username, std::string password);
	virtual int addNewUser(std::string username, std::string password, std::string email);

	//virtual int addQuestions(std::vector<std::uint8_t> buffer);

private:
	static int callbackCheckExistance(void* data, int argc, char** argv, char** azColName);


	//the database
	sqlite3* database;
};

