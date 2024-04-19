#pragma once
#include "Requests.h"
#include <vector>
#include <string>

struct RequestInfo
{
	int msgCode;
	int msgTime;
	std::vector<std::string> msgContant;
};

class JsonRequestPacketDeserializer
{
public:
	static RequestInfo deserializeLoginRequest(LoginRequest log);
	static RequestInfo deserializeSignUpRequest(SignupRequest sig);
};

#pragma once
