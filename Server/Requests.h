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
	PERSONAL_STATS
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

