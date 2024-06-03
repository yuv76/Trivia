#pragma once

#include <string>
#include <vector>

enum questionDifficulties
{
	easy = 0,
	medium, hard
};

struct QuestionData
{
	unsigned int id;
	std::string question;
	std::string rightAnswer;
	std::string wrongAnswer1;
	std::string wrongAnswer2;
	std::string wrongAnswer3;
	questionDifficulties difficulty;
};

class IDatabase
{
public:
	virtual ~IDatabase() = default;

	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual int doesUserExist(std::string username) = 0;
	virtual int doesPasswordMatch(std::string username, std::string password) = 0;
	virtual int addNewUser(std::string username, std::string password, std::string email) = 0;

	virtual std::vector<QuestionData> getQuestions(int questionNum) = 0;
	virtual float getPlayerAverageAnswerTime(std::string username) = 0;
	virtual int getNumOfCorrectAnswers(std::string username) = 0;
	virtual int getNumOfTotalAnswers(std::string username) = 0;
	virtual int getNumOfPlayerGames(std::string username) = 0;

	virtual void addNewQuestionsToDb(int numOfQuestions) = 0;

	virtual std::vector<std::string> getUsers() = 0;
};

