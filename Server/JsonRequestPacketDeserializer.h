#pragma once
#include "Requests.h"
#include <vector>
#include <string>
#include <ctime>

#define BYTE 8
#define INT_BYTES 4

struct RequestInfo
{
	int msgCode;
	time_t msgTime;
	std::vector<std::string> msgContant;
};

class JsonRequestPacketDeserializer
{
public:
	static RequestInfo deserializeLoginRequest(LoginRequest log);
	static RequestInfo deserializeSignUpRequest(SignupRequest sig);

private:
	static int binaryToDecimal(int n);
};

#pragma once
