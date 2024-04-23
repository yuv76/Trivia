#pragma once
#include <string>

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
