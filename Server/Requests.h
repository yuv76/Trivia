#pragma once

#include <string>

enum msgCodes
{
	ERR = 0,
	SIGNUP,
	LOGIN
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
