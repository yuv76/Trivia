#include "Question.h"

/*
Default C'tor for Question object.
in: none.
*/
Question::Question() 
{
	this->_id = 0;
	this->m_question = "";
	this->_correct = "";
}

/*
C'tor for Question object.
in: the question itself, 3 wrong answers, right answer, the question's id.
*/
Question::Question(std::string phrazing, std::string ans1, std::string ans2, std::string ans3, std::string correct, int id):
	m_question(phrazing), _id(id), _correct(correct)
{
	this->m_possibleAnswers.push_back(ans1);
	this->m_possibleAnswers.push_back(ans2);
	this->m_possibleAnswers.push_back(ans3);
	this->m_possibleAnswers.push_back(correct);

	//generate a rundom number for shuffle
	std::random_device rd;
	std::mt19937 g(rd());

	// Shuffle the answers vector. 
	std::shuffle(this->m_possibleAnswers.begin(), this->m_possibleAnswers.end(), g);
}

/*
returns the question's id.
in: none.
out: the id.
*/
int Question::getQuestionId()
{
	return this->_id;
}

/*
returns the question itself.
in: none.
out: the question.
*/
std::string Question::getQuestion()
{
	return this->m_question;
}

/*
returns the possible answers for the question.
in: none.
out: vector with the possible answers.
*/
std::vector<std::string> Question::getPossibleAnswers()
{
	return this->m_possibleAnswers;
}

/*
gets the correct answer to the question's id in the answers vector.
in: none.
out: the answer's index, or -1 if an error occured.
*/
int Question::getCorrectAnswerId()
{
	int i = 1;
	for (i = 1; i <= NUM_OF_ANSWERS; i++)
	{
		if (this->m_possibleAnswers[i] == this->_correct)
		{
			return i;
		}
	}
	return -1;// not suppsed to get here, if does it is a problem.
}

/*
sets the question to contain end of questions in game data.
in: none.
out: none.
*/
void Question::setEndQuestion()
{
	this->_id = -1;
	this->m_question = "No Questions left";
}

/*
sets the question to contain beggining of questions in game data.
in: none.
out: none.
*/
void Question::setStartQuestion()
{
	this->_id = 0;
	this->m_question = "First Question padding";
}