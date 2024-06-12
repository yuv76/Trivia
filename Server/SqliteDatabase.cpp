#include "SqliteDatabase.h"

#include <bitset>

#include <nlohmann/json.hpp>
using json = nlohmann::json;


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
		const char* createQuestionsTableSQL = "CREATE TABLE IF NOT EXISTS QUESTIONS (id INTEGER, [right answer] TEXT NOT NULL, [1 wrong answer] TEXT NOT NULL, [2 wrong answer] TEXT NOT NULL, [3 wrong answer] TEXT NOT NULL, question TEXT NOT NULL, difficulty TEXT NOT NULL, PRIMARY KEY(id AUTOINCREMENT)); ";
		const char* createStatisticsTableSQL = "CREATE TABLE IF NOT EXISTS STATISTICS (username TEXT PRIMARY KEY NOT NULL, [average time] REAL NOT NULL, [correct answers] INTEGER NOT NULL, [total answers] INTEGER NOT NULL, [player games] INTEGER NOT NULL); ";

		char* errMessage[100];
		//create users table
		res = sqlite3_exec(this->database, createUsersTableSQL, nullptr, nullptr, errMessage);
		if (res != SQLITE_OK)
		{
			throw std::exception(*errMessage);
		}

		//create questions table
		res = sqlite3_exec(this->database, createQuestionsTableSQL, nullptr, nullptr, errMessage);
		if (res != SQLITE_OK)
		{
			throw std::exception(*errMessage);
		}

		//create statistics table
		res = sqlite3_exec(this->database, createStatisticsTableSQL, nullptr, nullptr, errMessage);
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
out: 1 if match, 2 if user dosnt exist, 0 otherwise.
*/
int SqliteDatabase::doesPasswordMatch(std::string username, std::string password)
{
	char* errMessage[100];
	int match = 0;

	if (this->doesUserExist(username) == USER_DONT_EXIST)
	{
		match = USER_NOT_EXIST;
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
out: 1 if added sucessfully, 0 if user not added.
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


	addUserSQL = "INSERT INTO statistics  VALUES(\"" + username + "\", \"" + "0.00" + "\", \"" + '0' + "\", \"" + '0' + "\", \"" + '0' + "\"); ";
	res = sqlite3_exec(this->database, addUserSQL.c_str(), nullptr, nullptr, errMessage);
	if (res != SQLITE_OK)
	{
		throw std::exception(*errMessage);
	}
	return USER_ADDED;
}

/*
gets a question from the db.
in: the data(QuestionData pointer), number of fields in column, the field contents, the field names.
out: 0 upon sucess.
*/
int SqliteDatabase::callbackGetQuestion(void* data, int argc, char** argv, char** azColName)
{
	QuestionData* temp = static_cast<QuestionData*>(data);
	if (argc != 0)
	{
		for (int i = 0; i < argc; i++) {
			if (std::string(azColName[i]) == "id") {
				temp->id = atoi(argv[i]);
			}
			else if (std::string(azColName[i]) == "right answer") {
				temp->rightAnswer = argv[i];
			}
			else if (std::string(azColName[i]) == "1 wrong answer") {
				temp->wrongAnswer1 = argv[i];
			}
			else if (std::string(azColName[i]) == "2 wrong answer") {
				temp->wrongAnswer2 = argv[i];
			}
			else if (std::string(azColName[i]) == "3 wrong answer") {
				temp->wrongAnswer3 = argv[i];
			}
			else if (std::string(azColName[i]) == "question") {
				temp->question = argv[i];
			}
			else if (std::string(azColName[i]) == "difficulty") {
				if (argv[i] == "hard")
				{
					temp->difficulty = hard;
				}
				else if (argv[i] == "medium")
				{
					temp->difficulty = medium;
				}
				else
				{
					temp->difficulty = easy;
				}
			}
		}
	}
	return 0;
}

/*
gets questions from the db.
in: the number of questions to get.
out: a vector of questions.
*/
std::vector<QuestionData> SqliteDatabase::getQuestions(int questionNum)
{
	char* errMessage[100];
	QuestionData temp;
	std::vector<QuestionData> questionDatas;

	/*for (int i = 0; i <= questionNum; i++)
	{
		std::string getQuestionSQL = "select * from questions WHERE id == \"" + std::to_string((i + 1)) + "\";";
		int res = sqlite3_exec(this->database, getQuestionSQL.c_str(), callbackGetQuestion, &temp, errMessage);
		if (res != SQLITE_OK)
		{
			throw std::exception(*errMessage);
		}

		questionDatas.push_back(temp);
	}*/

	for (int i = 0; i < questionNum; i++)
	{
		std::string getQuestionSQL = "select * from questions ORDER BY RANDOM() LIMIT 1;";
		int res = sqlite3_exec(this->database, getQuestionSQL.c_str(), callbackGetQuestion, &temp, errMessage);
		if (res != SQLITE_OK)
		{
			throw std::exception(*errMessage);
		}
		for (auto& element : questionDatas)
		{
			if (element.id == temp.id)
			{
				i--;
				continue;
			}
		}
		temp.question = remove(temp.question);
		temp.rightAnswer = remove(temp.rightAnswer);
		temp.wrongAnswer1 = remove(temp.wrongAnswer1);
		temp.wrongAnswer2 = remove(temp.wrongAnswer2);
		temp.wrongAnswer3 = remove(temp.wrongAnswer3);
		questionDatas.push_back(temp);
	}
	
	return questionDatas;
}

std::string SqliteDatabase::remove(std::string temp)
{
	int first = temp.find('&');
	int last = temp.find(';');
	while (first != std::string::npos)
	{
		temp.erase(first, (last - first) + 1);
		//temp = temp.substr(0, last);
		first = temp.find('&');
		last = temp.find(';');
	}
	return temp;
}

/*
gets a the players average answer time from the db.
in: the data(float pointer), number of fields in column, the field contents, the field names.
out: 0 upon sucess.
*/
int SqliteDatabase::callbackGetAverageAnswerTime(void* data, int argc, char** argv, char** azColName)
{
	float* answerTime = static_cast<float*>(data);
	
	if (argc != 0)
	{
		for (int i = 0; i < argc; i++) {
			if (std::string(azColName[i]) == "average time") 
			{
				*answerTime = atoi(argv[i]);
			}
		}
	}
	return 0;
}

/*
gets the average answer time for a specific player.
in: the player's username.
out: the average (float).
*/
float SqliteDatabase::getPlayerAverageAnswerTime(std::string username)
{
	float answerTime;

	char* errMessage[100];
	
	std::string getStatisticsSQL = "select * from statistics WHERE USERNAME == \"" + username + "\";";
	int res = sqlite3_exec(this->database, getStatisticsSQL.c_str(), callbackGetAverageAnswerTime, &answerTime, errMessage);
	if (res != SQLITE_OK)
	{
		throw std::exception(*errMessage);
	}

	return answerTime;
}

/*
gets a the players num of correct answers from the db.
in: the data(int pointer), number of fields in column, the field contents, the field names.
out: 0 upon sucess.
*/
int SqliteDatabase::callbackGetNumOfCorrectAnswers(void* data, int argc, char** argv, char** azColName)
{
	int* num = static_cast<int*>(data);

	if (argc != 0)
	{
		for (int i = 0; i < argc; i++) {
			if (std::string(azColName[i]) == "correct answers")
			{
				*num = atoi(argv[i]);
			}
		}
	}
	return 0;
}

/*
gets number of user's correct answers.
in: the user's username.
out: the number of correct answers.
*/
int SqliteDatabase::getNumOfCorrectAnswers(std::string username)
{
	int num;

	char* errMessage[100];

	std::string getStatisticsSQL = "select * from statistics WHERE USERNAME == \"" + username + "\";";
	int res = sqlite3_exec(this->database, getStatisticsSQL.c_str(), callbackGetNumOfCorrectAnswers, &num, errMessage);
	if (res != SQLITE_OK)
	{
		throw std::exception(*errMessage);
	}

	return num;
}


/*
gets a the players num of total answers from the db.
in: the data(int pointer), number of fields in column, the field contents, the field names.
out: 0 upon sucess.
*/
int SqliteDatabase::callbackGetNumOfTotalAnswers(void* data, int argc, char** argv, char** azColName)
{
	int* num = static_cast<int*>(data);

	if (argc != 0)
	{
		for (int i = 0; i < argc; i++) {
			if (std::string(azColName[i]) == "total answers")
			{
				*num = atoi(argv[i]);
			}
		}
	}
	return 0;
}

/*
gets player's number of questions answers.
in: the player's username.
out: the number of questions answered.
*/
int SqliteDatabase::getNumOfTotalAnswers(std::string username)
{
	int num;

	char* errMessage[100];

	std::string getStatisticsSQL = "select * from statistics WHERE USERNAME == \"" + username + "\";";
	int res = sqlite3_exec(this->database, getStatisticsSQL.c_str(), callbackGetNumOfTotalAnswers, &num, errMessage);
	if (res != SQLITE_OK)
	{
		throw std::exception(*errMessage);
	}

	return num;
}

/*
gets a the players num of players games from the db.
in: the data(int pointer), number of fields in column, the field contents, the field names.
out: 0 upon sucess.
*/
int SqliteDatabase::callbackGetNumOfPlayerGames(void* data, int argc, char** argv, char** azColName)
{
	int* num = static_cast<int*>(data);

	if (argc != 0)
	{
		for (int i = 0; i < argc; i++) {
			if (std::string(azColName[i]) == "player games")
			{
				*num = atoi(argv[i]);
			}
		}
	}
	return 0;
}

/*
gets the number of player's games played from database, given the player's username.
in: the username of the player to get its questions.
out: the number of games.
*/
int SqliteDatabase::getNumOfPlayerGames(std::string username)
{
	int num;

	char* errMessage[100];

	std::string getStatisticsSQL = "select * from statistics WHERE USERNAME == \"" + username + "\";";
	int res = sqlite3_exec(this->database, getStatisticsSQL.c_str(), callbackGetNumOfPlayerGames, &num, errMessage);
	if (res != SQLITE_OK)
	{
		throw std::exception(*errMessage);
	}

	return num;
}

/*
adds n new questions to the database from opentdb.com.
in: the number of questions to get.
out: none.
*/
void SqliteDatabase::addNewQuestionsToDb(int numOfQuestions)
{
	std::string filename = "get_n_questions_from_online_db.py";
	std::string command = "python " + filename + " " + std::to_string(numOfQuestions);
	system(command.c_str());
}


/*
gets the users from the db.
in: the data(strings vector pointer), number of fields in column, the field contents, the field names.
out: 0 upon sucess.
*/
int SqliteDatabase::callbackGetUsers(void* data, int argc, char** argv, char** azColName)
{
	std::vector<std::string>* temp = static_cast<std::vector<std::string>*>(data);
	if (argc != 0)
	{
		for (int i = 0; i < argc; i++) {
			if (std::string(azColName[i]) == "USERNAME") {
				temp->push_back(argv[i]);
			}
		}
	}
	return 0;
}

/*
gets all of the users.
in: none.
out: a vector with the user names.
*/
std::vector<std::string> SqliteDatabase::getUsers()
{
	char* errMessage[100];
	std::string temp;
	std::vector<std::string> users;

	std::string getQuestionSQL = "select * from users;";
	int res = sqlite3_exec(this->database, getQuestionSQL.c_str(), callbackGetUsers, &users, errMessage);
	if (res != SQLITE_OK)
	{
		throw std::exception(*errMessage);
	}

	return users;
}


/*
gets the total answers of user and its average answer time from SQL database answer.
in: the data(Pair of double and int pointer), number of fields in column, the field contents, the field names.
out: 0 upon sucess.
*/
int SqliteDatabase::callbackGetAvgAndTotalAns(void* data, int argc, char** argv, char** azColName)
{
	std::pair<double, int>* temp = static_cast<std::pair<double, int>*>(data);
	if (argc != 0)
	{
		temp->first = std::atof(argv[0]);
		temp->second = int(std::atof((argv[1])));
	}
	return 0;
}

/*
updates game statistics for a user in the database.
in: the data of a game performed by the user.
out: 
*/
void SqliteDatabase::submitGameStatistics(GameData gd, std::string username)
{
	double oldAvg;
	double newAvg;
	double avgToUpdate;
	int totalAns;
	int gameTotalAns;
	std::pair<double, int> totalAndAvg;
	char* errMessage[100];

	//get previus number of answers and average.
	std::string getStatisticsSQL = "select [average time], [total answers] from statistics WHERE USERNAME == \"" + username + "\";";
	int res = sqlite3_exec(this->database, getStatisticsSQL.c_str(), callbackGetAvgAndTotalAns, &totalAndAvg, errMessage);
	if (res != SQLITE_OK)
	{
		throw std::exception(*errMessage);
	}

	oldAvg = totalAndAvg.first;
	totalAns = totalAndAvg.second;
	oldAvg *= totalAns;

	gameTotalAns = gd.correctAnswerCount + gd.wrongAnswerCount;
	newAvg = gd.averangeAnswerTime;
	newAvg *= gameTotalAns;

	avgToUpdate = newAvg + oldAvg;
	avgToUpdate /= (gameTotalAns + totalAns);

	std::string sqlUpdateQuery = "UPDATE STATISTICS SET [average time] = " + std::to_string(avgToUpdate) + ", [correct answers] = [correct answers] + " + std::to_string(gd.correctAnswerCount) + ", [total answers] = [total answers] + " + std::to_string(gameTotalAns) + ", [player games] = [player games] + 1 WHERE username = \"" + username + "\"; ";
	res = sqlite3_exec(this->database, sqlUpdateQuery.c_str(), nullptr, nullptr, errMessage);
	if (res != SQLITE_OK)
	{
		throw std::exception(*errMessage);
	}
}
