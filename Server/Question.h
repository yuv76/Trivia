#pragma once
#include <string>
#include <vector>

class Question
{
private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
public:
	std::string getQuestion();
	std::vector<std::string> getPossibleAnswers();
	int getCorrectAnswerId();
};