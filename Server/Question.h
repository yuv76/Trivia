#pragma once
#include <string>
#include <vector>
#include <random>
#include <algorithm>

#define NUM_OF_ANSWERS 4

class Question
{
private:
	int _id;
	std::string m_question;
	std::string _correct;
	std::vector<std::string> m_possibleAnswers;
public:
	Question();
	Question(std::string phrazing, std::string ans1, std::string ans2, std::string ans3, std::string correct, int id);

	int getQuestionId();
	std::string getQuestion();
	std::vector<std::string> getPossibleAnswers();
	int getCorrectAnswerId();
	void setEndQuestion();
	void setStartQuestion();
};