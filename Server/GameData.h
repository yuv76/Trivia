#pragma once
#include "Question.h"

#define GOT_QUESTION 1

struct GameData
{
	//default C'tor
	GameData() {}

	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averangeAnswerTime;
	bool isActive;
};