#pragma once
#include "Responses.h"
#include <vector>
#include <string>

enum msgCodes
{
	ERR = 0,
	SIGNUP,
	LOGIN
};

#define BYTE 8
#define INT_BYTES 4

class JsonResponsePacketSerializer
{
public:
	static std::vector<std::uint8_t> serializeErrorResponse(ErrorResponse err);
	static std::vector<std::uint8_t> serializeLoginResponse(LoginResponse log);
	static std::vector<std::uint8_t> serializeSignUpResponse(SignupResponse sig);
};

	