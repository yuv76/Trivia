#include "JsonResponsePacketSerializer.h"
#include <bitset>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse err)
{
	std::vector<std::uint8_t> buffer;
	std::vector<std::uint8_t> tampMsg;
	std::string msg = err.message;
	msgCodes code = ERR;
	int len = 0;

	json errJson;

	//add code byte to vector
	buffer.push_back(static_cast<std::uint8_t>(code & 0xFF)); // only one byte

	//create msg in json format
	errJson["message"] = err.message;
	msg = errJson.dump();

	//add length to vector as 4 binary bytes - shifting the integer value to the right by 8 bits each time.
	len = msg.length();
	buffer.push_back(static_cast<std::uint8_t>((len >> 24) & 0xFF)); 
	buffer.push_back(static_cast<std::uint8_t>((len >> 16) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>((len >> 8) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>(len & 0xFF)); 

	//add message in bytes to the vector
	tampMsg = json::to_ubjson(errJson);
	buffer.insert(buffer.end(), tampMsg.begin(), tampMsg.end());

	return buffer;
}

std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse log)
{
	std::vector<std::uint8_t> buffer;
	std::vector<std::uint8_t> tempMsg;
	std::string msg = "";
	msgCodes code = LOGIN;
	int len = 0;
	json loginJson;

	//add code byte to vector
	buffer.push_back(static_cast<std::uint8_t>(code & 0xFF)); //only one byte

	//create msg in json format
	loginJson["status"] = log.status;
	msg = loginJson.dump();

	//add length to vector as 4 binary bytes - shifting the integer value to the right by 8 bits each time.
	len = msg.length();
	buffer.push_back(static_cast<std::uint8_t>((len >> 24) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>((len >> 16) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>((len >> 8) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>(len & 0xFF));

	//add message in bytes to the vector
	tempMsg = json::to_ubjson(loginJson);
	buffer.insert(buffer.end(), tempMsg.begin(), tempMsg.end());

	return buffer;
}

std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeSignUpResponse(SignupResponse sig)
{
	std::vector<std::uint8_t> buffer;
	std::vector<std::uint8_t> tempMsg;
	std::string msg = "";
	msgCodes code = SIGNUP;
	int len = 0;
	json signupJson;

	//add code byte to vector
	buffer.push_back(static_cast<std::uint8_t>(code & 0xFF)); //only one byte

	//create msg in json format
	signupJson["status"] = sig.status;
	msg = signupJson.dump();

	//add length to vector as 4 binary bytes - shifting the integer value to the right by 8 bits each time.
	len = msg.length();
	buffer.push_back(static_cast<std::uint8_t>((len >> 24) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>((len >> 16) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>((len >> 8) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>(len & 0xFF));

	//add message in bytes to the vector
	tempMsg = json::to_ubjson(signupJson);
	buffer.insert(buffer.end(), tempMsg.begin(), tempMsg.end());

	return buffer;
}