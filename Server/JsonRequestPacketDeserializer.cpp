#include "JsonRequestPacketDeserializer.h"
#include <bitset>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

/*
deserializes a login request.
in: the bytes vector buffer containing the login message.
out: LoginRequest struct presenting the request.
*/
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

/*
deserializes a signup request.
in: the bytes vector buffer containing the signup message.
out: SignupRequest struct presenting the request.
*/
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


/*
deserializes a get players in room request.
in: the bytes vector buffer containing the get players in room message.
out: GetPlayersInRoomRequest struct presenting the request.
*/
GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(std::vector<std::uint8_t> buffer)
{
	GetPlayersInRoomRequest info;
	json jsonBuf;

	// remove the code and len from the vector.
	buffer.erase(buffer.begin(), buffer.begin() + MSG_HEADER);
	// convert the recieved bytes back to a vector.
	jsonBuf = json::from_ubjson(buffer);

	//roomId
	info.roomId = jsonBuf["roomId"];
	
	return info;
}

/*
deserializes a join room request.
in: the bytes vector buffer containing the join room message.
out: JoinRoomRequest struct presenting the request.
*/
JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<std::uint8_t> buffer)
{
	JoinRoomRequest info;
	json jsonBuf;

	// remove the code and len from the vector.
	buffer.erase(buffer.begin(), buffer.begin() + MSG_HEADER);
	// convert the recieved bytes back to a vector.
	jsonBuf = json::from_ubjson(buffer);

	//roomId
	info.roomId = jsonBuf["roomId"];

	return info;
}

/*
deserializes a create room request.
in: the bytes vector buffer containing the create room message.
out: CreateRoomRequest struct presenting the request.
*/
CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<std::uint8_t> buffer)
{
	CreateRoomRequest info;
	json jsonBuf;

	// remove the code and len from the vector.
	buffer.erase(buffer.begin(), buffer.begin() + MSG_HEADER);
	// convert the recieved bytes back to a vector.
	jsonBuf = json::from_ubjson(buffer);

	//roomName
	info.roomName = jsonBuf["roomName"];
	//maxUsers
	info.maxUsers = jsonBuf["maxUsers"];
	//questionCount
	info.questionCount = jsonBuf["questionCount"];
	//anwerTimeout
	info.anwerTimeout = jsonBuf["anwerTimeout"];

	return info;
}