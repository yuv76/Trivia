#include "JsonResponsePacketSerializer.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

/*
serializes an error response into a byte vector.
in: the error response at the form of an ErrorResponse struct.
out: the bytes vector containing the response.
*/
std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeResponse(ErrorResponse err)
{
	std::vector<std::uint8_t> buffer;
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
	std::vector<std::uint8_t> tempMsg(msg.begin(), msg.end());

	buffer.insert(buffer.end(), tempMsg.begin(), tempMsg.end());

	return buffer;
}

/*
serializes a login response into a byte vector.
in: the signup response at the form of a LoginResponse struct.
out: the bytes vector containing the response.
*/
std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeResponse(LoginResponse log)
{
	std::vector<std::uint8_t> buffer;
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
	std::vector<std::uint8_t> tempMsg(msg.begin(), msg.end());

	buffer.insert(buffer.end(), tempMsg.begin(), tempMsg.end());

	return buffer;
}

/*
serializes a signup response into a byte vector.
in: the signup response at the form of a SignupResponse struct.
out: the bytes vector containing the response.
*/
std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeResponse(SignupResponse sig)
{
	std::vector<std::uint8_t> buffer;
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
	std::vector<std::uint8_t> tempMsg(msg.begin(), msg.end());

	buffer.insert(buffer.end(), tempMsg.begin(), tempMsg.end());

	return buffer;
}

/*
serializes a logout response into a byte vector.
in: the logout response at the form of a LogoutResponse struct.
out: the bytes vector containing the response.
*/
std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeResponse(LogoutResponse log)
{
	std::vector<std::uint8_t> buffer;
	std::string msg = "";
	msgCodes code = SIGNOUT;
	int len = 0;
	json logoutJson;

	//add code byte to vector
	buffer.push_back(static_cast<std::uint8_t>(code & 0xFF)); //only one byte

	//create msg in json format
	logoutJson["status"] = log.status;
	msg = logoutJson.dump();

	//add length to vector as 4 binary bytes - shifting the integer value to the right by 8 bits each time.
	len = msg.length();
	buffer.push_back(static_cast<std::uint8_t>((len >> 24) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>((len >> 16) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>((len >> 8) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>(len & 0xFF));

	//add message in bytes to the vector
	std::vector<std::uint8_t> tempMsg(msg.begin(), msg.end());

	buffer.insert(buffer.end(), tempMsg.begin(), tempMsg.end());

	return buffer;
}

/*
serializes a get room response into a byte vector.
in: the get rooms response at the form of a GetRoomsResponse struct.
out: the bytes vector containing the response.
*/
std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse getR)
{
	std::vector<std::uint8_t> buffer;
	std::vector<std::pair<std::string, std::string>> rooms;
	std::string msg = "";
	msgCodes code = GET_ROOM;
	int len = 0;
	json getRoomJson;

	//add code byte to vector
	buffer.push_back(static_cast<std::uint8_t>(code & 0xFF)); //only one byte

	auto i = getR.rooms.begin();
	for (i; i != getR.rooms.end(); i++) // propably will need to contain more info, can be in another json field and each room by its index, see after will be needed. #todo
	{
		rooms.push_back(std::make_pair(std::to_string(i->id), i->name));
	}

	//create msg in json format
	getRoomJson["status"] = getR.status;
	getRoomJson["Rooms"] = rooms;
	msg = getRoomJson.dump();

	//add length to vector as 4 binary bytes - shifting the integer value to the right by 8 bits each time.
	len = msg.length();
	buffer.push_back(static_cast<std::uint8_t>((len >> 24) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>((len >> 16) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>((len >> 8) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>(len & 0xFF));

	//add message in bytes to the vector
	std::vector<std::uint8_t> tempMsg(msg.begin(), msg.end());

	buffer.insert(buffer.end(), tempMsg.begin(), tempMsg.end());

	return buffer;
}

/*
serializes a get players in room response into a byte vector.
in: the get players in room response at the form of a GetPlayersInRoomResponse struct.
out: the bytes vector containing the response.
*/
std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse getP)
{
	std::vector<std::uint8_t> buffer;
	std::string msg = "";
	std::vector<std::string> players;
	msgCodes code = GET_PLAYERS;
	int len = 0;
	json getPlayersJson;

	//add code byte to vector
	buffer.push_back(static_cast<std::uint8_t>(code & 0xFF)); //only one byte

	//create msg in json format
	getPlayersJson["Players"] = getP.players;
	getPlayersJson["Admin"] = getP.roomAdmin;
	msg = getPlayersJson.dump();

	//add length to vector as 4 binary bytes - shifting the integer value to the right by 8 bits each time.
	len = msg.length();
	buffer.push_back(static_cast<std::uint8_t>((len >> 24) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>((len >> 16) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>((len >> 8) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>(len & 0xFF));

	//add message in bytes to the vector
	std::vector<std::uint8_t> tempMsg(msg.begin(), msg.end());

	buffer.insert(buffer.end(), tempMsg.begin(), tempMsg.end());

	return buffer;
}

/*
serializes a join room response into a byte vector.
in: the join room response at the form of a JoinRoomResponse struct.
out: the bytes vector containing the response.
*/
std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse join)
{	
	std::vector<std::uint8_t> buffer;
	std::string msg = "";
	msgCodes code = JOIN_ROOM;
	int len = 0;
	json joinRoomJson;

	//add code byte to vector
	buffer.push_back(static_cast<std::uint8_t>(code & 0xFF)); //only one byte

	//create msg in json format
	joinRoomJson["status"] = join.status;
	msg = joinRoomJson.dump();

	//add length to vector as 4 binary bytes - shifting the integer value to the right by 8 bits each time.
	len = msg.length();
	buffer.push_back(static_cast<std::uint8_t>((len >> 24) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>((len >> 16) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>((len >> 8) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>(len & 0xFF));

	//add message in bytes to the vector
	std::vector<std::uint8_t> tempMsg(msg.begin(), msg.end());

	buffer.insert(buffer.end(), tempMsg.begin(), tempMsg.end());

	return buffer;
}

/*
serializes a create room response into a byte vector.
in: the create room response at the form of a CreateRoomResponse struct.
out: the bytes vector containing the response.
*/
std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse crea)
{
	std::vector<std::uint8_t> buffer;
	std::string msg = "";
	msgCodes code = CREATE_ROOM;
	int len = 0;
	json createRoomJson;

	//add code byte to vector
	buffer.push_back(static_cast<std::uint8_t>(code & 0xFF)); //only one byte

	//create msg in json format
	createRoomJson["id"] = crea.id;
	createRoomJson["status"] = crea.status;
	msg = createRoomJson.dump();

	//add length to vector as 4 binary bytes - shifting the integer value to the right by 8 bits each time.
	len = msg.length();
	buffer.push_back(static_cast<std::uint8_t>((len >> 24) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>((len >> 16) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>((len >> 8) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>(len & 0xFF));

	//add message in bytes to the vector
	std::vector<std::uint8_t> tempMsg(msg.begin(), msg.end());

	buffer.insert(buffer.end(), tempMsg.begin(), tempMsg.end());

	return buffer;
}

/*
serializes a get high score response into a byte vector.
in: the get high score response at the form of a getHighScoreResponse struct.
out: the bytes vector containing the response.
*/
std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeResponse(getHighScoreResponse high)
{
	std::vector<std::uint8_t> buffer;
	std::vector<std::string> stats;
	std::string msg = "";
	msgCodes code = HIGH_SCORE;
	int len = 0;
	json getPlayersJson;

	//add code byte to vector
	buffer.push_back(static_cast<std::uint8_t>(code & 0xFF)); //only one byte

	auto i = high.statistics.begin();
	for (i; i != high.statistics.end(); i++) //will have to be expanded according to what will be in the statistics part.
	{
		stats.push_back(*i);
	}

	//create msg in json format
	getPlayersJson["status"] = high.status;
	getPlayersJson["statistics"] = stats;
	msg = getPlayersJson.dump();

	//add length to vector as 4 binary bytes - shifting the integer value to the right by 8 bits each time.
	len = msg.length();
	buffer.push_back(static_cast<std::uint8_t>((len >> 24) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>((len >> 16) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>((len >> 8) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>(len & 0xFF));

	//add message in bytes to the vector
	std::vector<std::uint8_t> tempMsg(msg.begin(), msg.end());

	buffer.insert(buffer.end(), tempMsg.begin(), tempMsg.end());

	return buffer;
}

/*
serializes a get get personal stats response into a byte vector.
in: the get personal stats response at the form of a getPersonalStatsResponse struct.
out: the bytes vector containing the response.
*/
std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeResponse(getPersonalStatsResponse pers)
{
	std::vector<std::uint8_t> buffer;
	std::string msg = "";
	std::string stats = "";
	msgCodes code = PERSONAL_STATS;
	int len = 0;
	json getPlayersJson;

	//add code byte to vector
	buffer.push_back(static_cast<std::uint8_t>(code & 0xFF)); //only one byte

	auto i = pers.statistics.begin();
	for (i; i != pers.statistics.end(); i++) //will have to be expanded according to what will be in the statistics part.
	{
		stats += *i;
		stats += ",";
	}

	//create msg in json format
	getPlayersJson["status"] = pers.status;
	getPlayersJson["statistics"] = stats;
	msg = getPlayersJson.dump();

	//add length to vector as 4 binary bytes - shifting the integer value to the right by 8 bits each time.
	len = msg.length();
	buffer.push_back(static_cast<std::uint8_t>((len >> 24) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>((len >> 16) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>((len >> 8) & 0xFF));
	buffer.push_back(static_cast<std::uint8_t>(len & 0xFF));

	//add message in bytes to the vector
	std::vector<std::uint8_t> tempMsg(msg.begin(), msg.end());

	buffer.insert(buffer.end(), tempMsg.begin(), tempMsg.end());

	return buffer;
}
