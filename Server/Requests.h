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

