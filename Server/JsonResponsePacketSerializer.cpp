#include "JsonResponsePacketSerializer.h"
#include <bitset>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

std::vector<std::string> JsonResponsePacketSerializer::serializeResponse(ErrorResponse err)
{
	std::vector<std::string> buffer;
	std::string msg = "";
	std::string tampBinary = "";
	int len = 0;
	int i = 0;

	json errJson;

	//code byte
	tampBinary = std::bitset<BYTE>(ERR).to_string(); //to binary
	buffer.push_back(tampBinary);

	//create msg in json format
	errJson["message"] = err.message;
	msg = errJson.dump();

	//length to 4 binary bytes
	len = msg.length();
	tampBinary = std::bitset<BYTE*INT_BYTES>(len).to_string();
	buffer.push_back(tampBinary);

	//the message in bytes
	tampBinary = "";
	for (i = 0; i < len; i++) //convert 
	{
		tampBinary += std::bitset<BYTE>(msg[i]).to_string();
	}
	buffer.push_back(tampBinary);

	return buffer;
}

std::vector<std::string> JsonResponsePacketSerializer::serializeResponse(LoginResponse log)
{
	std::vector<std::string> buffer;
	std::string tempBinary = "";
	std::string msg = "";
	int len = 0;
	int i = 0;
	json loginJson;

	//code byte
	tempBinary = std::bitset<BYTE>(LOGIN).to_string(); //to binary
	buffer.push_back(tempBinary);

	//create msg in json format
	loginJson["status"] = log.status;
	msg = loginJson.dump();

	//length to 4 binary bytes
	len = msg.length();
	tempBinary = std::bitset<BYTE * INT_BYTES>(len).to_string();
	buffer.push_back(tempBinary);

	//the message in bytes
	tempBinary = "";
	for (i = 0; i < len; i++) //convert 
	{
		tempBinary += std::bitset<BYTE>(msg[i]).to_string();
	}
	buffer.push_back(tempBinary);

	return buffer;
}

std::vector<std::string> JsonResponsePacketSerializer::serializeResponse(SignupResponse sig)
{
	std::vector<std::string> buffer;
	std::string tempBinary = "";
	std::string msg = "";
	int len = 0;
	int i = 0;
	json signupJson;

	//code byte
	tempBinary = std::bitset<BYTE>(SIGNUP).to_string(); //to binary
	buffer.push_back(tempBinary);

	//create msg in json format
	signupJson["status"] = sig.status;
	msg = signupJson.dump();

	//length to 4 binary bytes
	len = msg.length();
	tempBinary = std::bitset<BYTE * INT_BYTES>(len).to_string();
	buffer.push_back(tempBinary);

	//the message in bytes
	tempBinary = "";
	for (i = 0; i < len; i++) //convert 
	{
		tempBinary += std::bitset<BYTE>(msg[i]).to_string();
	}
	buffer.push_back(tempBinary);

	return buffer;
}