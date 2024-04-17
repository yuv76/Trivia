#pragma once
#include <string>

struct SignupRequest
{
public:
	std::string username;
	std::string password;
}; 

struct LoginRequest
{
public:
	std::string username;
	std::string password;
	std::string email;
};