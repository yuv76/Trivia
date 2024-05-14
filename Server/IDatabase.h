#pragma once

#include <string>
#include <vector>

struct QuestionData
{
	unsigned int id;
	std::string question;
	std::string rightAnswer;
	std::string wrongAnswer1;
	std::string wrongAnswer2;
	std::string wrongAnswer3;
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
};

