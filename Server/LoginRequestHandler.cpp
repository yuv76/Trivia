#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"


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
	RequestResult res;
	json result;
	if (inf.RequestId == LOGIN)
	{
		LoginRequest log = JsonRequestPacketDeserializer::deserializeLoginRequest(inf.buffer);
		//check the message i guess
		result["status"] = 1;
	}
	else //sign up
	{
		SignupRequest log = JsonRequestPacketDeserializer::deserializeSignUpRequest(inf.buffer);
		//check the message i guess
		result["status"] = 1;
	}
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