#pragma once

#include <string>

enum msgCodes
{
	ERR = 0,
	SIGNUP,
	LOGIN,
	SIGNOUT,
	GET_ROOM,
	GET_PLAYERS,
	JOIN_ROOM,
	CREATE_ROOM,
	HIGH_SCORE,
	PERSONAL_STATS,
	DISCONNECT,

	CLOSE_ROOM,
	START_GAME,
	GET_ROOM_STATE,
	LEAVE_ROOM,

	LEAVE_GAME,
	GET_QUESTION,
	SUBMIT_ANSWER,
	GET_GAME_RESULTS,
	RETURN_TO_ROOM
};

struct LoginRequest
{
public:
	std::string username;
	std::string password;
}; 

struct SignupRequest
{
public:
	std::string username;
	std::string password;
	std::string email;
};

struct GetPlayersInRoomRequest
{
public:
	unsigned int roomId;
};

struct JoinRoomRequest
{
public:
	unsigned int roomId;
};

struct CreateRoomRequest
{
public:
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int anwerTimeout;
};

struct SubmitAnswerRequest
{
public:
	unsigned int answerId;
	double answerTime;
};