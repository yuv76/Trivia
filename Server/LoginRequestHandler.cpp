#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;


bool LoginRequestHandler::isRequestRelevant(RequestInfo inf)
{
	bool relevant = false;
	if (inf.RequestId == LOGIN || inf.RequestId == SIGNUP)
	{
		relevant = true;
	}
	return relevant;
}

RequestResult handleRequest(RequestInfo inf)
{
	std::vector<std::uint8_t> buffer;
	RequestResult res;
	json result;
	if (inf.RequestId == LOGIN)
	{
		LoginRequest log = JsonRequestPacketDeserializer::deserializeLoginRequest(inf.buffer);
		LoginResponse l;
		//check the message i guess, if error should return error, but no way to check now
		l.status = 1;
		buffer = JsonResponsePacketSerializer::serializeLoginResponse(l);
		res.response = buffer;
		//res.newHandler  - ???
	}
	else //sign up
	{
		SignupRequest log = JsonRequestPacketDeserializer::deserializeSignUpRequest(inf.buffer);
		SignupResponse s;
		//check the message
		s.status = 1;
		buffer = JsonResponsePacketSerializer::serializeSignUpResponse(s);
		res.response = buffer;
	}
	return res;
}


/*
// Function to convert binary 
// to decimal 
int LoginRequestHandler::binaryToDecimal(int n)
{
	int num = n;
	int dec_value = 0;

	// Initializing base value to 
	// 1, i.e 2^0 
	int base = 1;

	int temp = num;
	while (temp) {
		int last_digit = temp % 10;
		temp = temp / 10;
		dec_value += last_digit * base;
		base = base * 2;
	}

	return dec_value;
}*/