#pragma once

#include "Responses.h"
#include "Requests.h"
#include <vector>
#include <string>

class JsonResponsePacketSerializer
{
public:
	static std::vector<std::uint8_t> serializeErrorResponse(ErrorResponse err);
	static std::vector<std::uint8_t> serializeLoginResponse(LoginResponse log);
	static std::vector<std::uint8_t> serializeSignUpResponse(SignupResponse sig);
};
