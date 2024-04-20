#include "JsonRequestPacketDeserializer.h"
#include <bitset>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

RequestInfo JsonRequestPacketDeserializer::deserializeLoginRequest(LoginRequest log)
{
	RequestInfo info;
	std::vector<std::string> buffer;

	//code byte
	info.msgCode = 2;

	info.msgTime = time(0);

	// the msg is not in the LoginRequest so what are we supposed to put in it?

	return info;
}

RequestInfo JsonRequestPacketDeserializer::deserializeSignUpRequest(SignupRequest sig)
{
	RequestInfo info;
	std::vector<std::string> buffer;

	//code byte
	info.msgCode = 1;

	info.msgTime = time(0);

	// same thing the msg is not in the SignupRequest so what are we supposed to put in it?

	return info;
}



// Function to convert binary 
// to decimal 
int JsonRequestPacketDeserializer::binaryToDecimal(int n)
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
}