#pragma once

#include "RoomData.h"
#include <vector>

struct SignupResponse
{
public:
	unsigned int status;
};

struct LoginResponse
{
public:
	unsigned int status;
};

struct ErrorResponse
{
public:
	std::string message;
};

struct LogoutResponse
{
	unsigned int status;
};

struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse
{
	std::string roomAdmin;
	std::vector<std::string> players;
};

struct getHighScoreResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
};

struct getPersonalStatsResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
};

struct JoinRoomResponse
{
	int status;
};

struct CreateRoomResponse
{
	int id;
	unsigned int status;
};
