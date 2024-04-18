#pragma once
#include "Responses.h"
#include <vector>
#include <string>

enum msgCodes
{
	ERROR = 0, 
	SIGNUP,
	LOGIN
};

class JsonResponsePacketSerializer
{
	static std::vector<std::string> serializeResponse(ErrorResponse err);
	static std::vector<std::string> serializeResponse(LoginResponse log);
	static std::vector<std::string> serializeResponse(SignupResponse sig);
};

	