#pragma once
#include "Question.h"

struct GameData
{
	GameData() {};
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averangeAnswerTime;
	bool isActive;
};