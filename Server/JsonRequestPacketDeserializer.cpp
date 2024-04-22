#include "JsonRequestPacketDeserializer.h"
#include <bitset>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<std::uint8_t> buffer)
{
	LoginRequest info;
	json jsonBuf;
	
	// remove the code and len from the vector.
	buffer.erase(buffer.begin(), buffer.begin() + MSG_HEADER); 
	// convert the recieved bytes back to a Json.
	jsonBuf = json::from_ubjson(buffer); 

	//username
	info.username = jsonBuf["username"];
	//password
	info.password = jsonBuf["password"];

	return info;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(std::vector<std::uint8_t> buffer)
{
	SignupRequest info;
	json jsonBuf;

	// remove the code and len from the vector.
	buffer.erase(buffer.begin(), buffer.begin() + MSG_HEADER);
	// convert the recieved bytes back to a vector.
	jsonBuf = json::from_ubjson(buffer);

	//username
	info.username = jsonBuf["username"];
	//password
	info.password = jsonBuf["password"];
	//email
	info.email = jsonBuf["email"];

	return info;
}


/* still needed?
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
}*/