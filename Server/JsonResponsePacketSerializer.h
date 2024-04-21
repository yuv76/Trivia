#pragma once
#include "Responses.h"
#include <vector>
#include <string>

#define BYTE 8
#define INT_BYTES 4

class JsonResponsePacketSerializer
{
public:
	static std::vector<std::string> serializeErrorResponse(ErrorResponse err);
	static std::vector<std::string> serializeLoginResponse(LoginResponse log);
	static std::vector<std::string> serializeSignUpResponse(SignupResponse sig);
};

	