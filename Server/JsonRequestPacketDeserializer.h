#pragma once
#include "Requests.h"
#include <vector>
#include <string>

#define BYTE 8
#define INT_BYTES 4

#define MSG_HEADER 5

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<std::uint8_t> buffer);
	static SignupRequest deserializeSignUpRequest(std::vector<std::uint8_t> buffer);

//private:
	//static int binaryToDecimal(int n);
};
