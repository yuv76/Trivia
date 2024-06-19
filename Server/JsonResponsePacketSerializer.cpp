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
	for (i; i != getR.rooms.end(); i++)
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

/*
serializes a close room response into a byte vector.
in: the close room response at the form of a CloseRoomResponse struct.
out: the bytes vector containing the response.
*/
std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse close)
{
	std::vector<std::uint8_t> buffer;
	std::string msg = "";
	msgCodes code = CLOSE_ROOM;
	int len = 0;
	json closeRoomJson;

	//add code byte to vector
	buffer.push_back(static_cast<std::uint8_t>(code & 0xFF)); //only one byte

	//create msg in json format
	closeRoomJson["status"] = close.status;
	msg = closeRoomJson.dump();

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
serializes a start game response into a byte vector.
in: the start game response at the form of a StartGameResponse struct.
out: the bytes vector containing the response.
*/
std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeResponse(StartGameResponse start)
{
	std::vector<std::uint8_t> buffer;
	std::string msg = "";
	msgCodes code = START_GAME;
	int len = 0;
	json startGameJson;

	//add code byte to vector
	buffer.push_back(static_cast<std::uint8_t>(code & 0xFF)); //only one byte

	//create msg in json format
	startGameJson["status"] = start.status;
	msg = startGameJson.dump();

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
serializes a leave room response into a byte vector.
in: the leave room response at the form of a LeaveRoomResponse struct.
out: the bytes vector containing the response.
*/
std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse leave)
{
	std::vector<std::uint8_t> buffer;
	std::string msg = "";
	msgCodes code = LEAVE_ROOM;
	int len = 0;
	json leaveRoomJson;

	//add code byte to vector
	buffer.push_back(static_cast<std::uint8_t>(code & 0xFF)); //only one byte

	//create msg in json format
	leaveRoomJson["status"] = leave.status;
	msg = leaveRoomJson.dump();

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
serializes a get room stats response into a byte vector.
in: the get room stats response at the form of a GetRoomStateResponse struct.
out: the bytes vector containing the response.
*/
std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse stat)
{
	std::vector<std::uint8_t> buffer;
	std::string msg = "";
	std::string playerslist = "";
	msgCodes code = GET_ROOM_STATE;
	int len = 0;
	json getRoomStateJson;

	//add code byte to vector
	buffer.push_back(static_cast<std::uint8_t>(code & 0xFF)); //only one byte

	//create msg in json format
	getRoomStateJson["status"] = stat.status;
	getRoomStateJson["hasGameBegun"] = stat.hasGameBegun;
	getRoomStateJson["players"] = stat.players;
	getRoomStateJson["AnswerCount"] = stat.AnswerCount;
	getRoomStateJson["answerTimeOut"] = stat.answerTimeOut;
	getRoomStateJson["admin"] = stat.owner;
	getRoomStateJson["maxPlayers"] = stat.maxPlayers;
	msg = getRoomStateJson.dump();

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
serializes a leave game response into a byte vector.
in: the leave game response at the form of a LeaveGameResponse struct.
out: the bytes vector containing the response.
*/
std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeResponse(LeaveGameResponse leave)
{
	std::vector<std::uint8_t> buffer;
	std::string msg = "";
	msgCodes code = LEAVE_GAME;
	int len = 0;
	json leaveGameJson;

	//add code byte to vector
	buffer.push_back(static_cast<std::uint8_t>(code & 0xFF)); //only one byte

	//create msg in json format
	leaveGameJson["status"] = leave.status;
	msg = leaveGameJson.dump();

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
serializes a get room question into a byte vector.
in: the get question response at the form of a GetQuestionResponse struct.
out: the bytes vector containing the response.
*/
std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeResponse(GetQuestionResponse question)
{
	std::vector<std::uint8_t> buffer;
	std::vector<std::string> answers;
	std::string msg = "";
	msgCodes code = GET_QUESTION;
	int len = 0;
	json getQuestionJson;

	//add code byte to vector
	buffer.push_back(static_cast<std::uint8_t>(code & 0xFF)); //only one byte

	auto i = question.answers.begin();
	for (i; i != question.answers.end(); i++)
	{
		answers.push_back(*i);
	}
	//create msg in json format
	getQuestionJson["status"] = question.status;
	getQuestionJson["question"] = question.question;
	getQuestionJson["answers"] = answers;
	msg = getQuestionJson.dump();

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
serializes a submit answer response into a byte vector.
in: the submit answer response at the form of a SubmitAnswerResponse struct.
out: the bytes vector containing the response.
*/
std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeResponse(SubmitAnswerResponse answer)
{
	std::vector<std::uint8_t> buffer;
	std::string msg = "";
	msgCodes code = SUBMIT_ANSWER;
	int len = 0;
	json submitAnsweJson;

	//add code byte to vector
	buffer.push_back(static_cast<std::uint8_t>(code & 0xFF)); //only one byte

	//create msg in json format
	submitAnsweJson["status"] = answer.status;
	submitAnsweJson["correctAnswerId"] = answer.correctAnswerId;
	msg = submitAnsweJson.dump();

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
serializes a get game results response into a byte vector.
in: the get game results response at the form of a GetGameResultsResponse struct.
out: the bytes vector containing the response.
*/
std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeResponse(GetGameResultsResponse result)
{
	std::vector<std::uint8_t> buffer;
	std::vector<std::string> player;
	std::vector<std::string> rightAnsNum;
	std::vector<std::string> avgs;
	std::string msg = "";
	msgCodes code = GET_GAME_RESULTS;
	int len = 0;
	json getGameResultsJson;

	//add code byte to vector
	buffer.push_back(static_cast<std::uint8_t>(code & 0xFF)); //only one byte

	auto i = result.results.begin();
	for (i; i != result.results.end(); i++)
	{
		player.push_back((i->username));
		rightAnsNum.push_back(std::to_string(i->coorect));
		avgs.push_back(std::to_string(i->average));
	}

	//create msg in json format
	getGameResultsJson["status"] = result.status;
	getGameResultsJson["players"] = player;
	getGameResultsJson["Averages"] = avgs;
	getGameResultsJson["Corrects"] = rightAnsNum;
	msg = getGameResultsJson.dump();

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
serializes a return to room response into a byte vector.
in: the return to room response at the form of a returnToRoomResponse struct.
out: the bytes vector containing the response.
*/
std::vector<std::uint8_t> JsonResponsePacketSerializer::serializeResponse(returnToRoomResponse result)
{
	std::vector<std::uint8_t> buffer;
	std::string msg = "";
	msgCodes code = RETURN_TO_ROOM;
	int len = 0;
	json submitAnsweJson;

	//add code byte to vector
	buffer.push_back(static_cast<std::uint8_t>(code & 0xFF)); //only one byte

	//create msg in json format
	submitAnsweJson["status"] = result.status;
	submitAnsweJson["numOfPlayers"] = result.numOfPlayers;
	submitAnsweJson["roomId"] = result.roomId;
	submitAnsweJson["roomName"] = result.roomName;
	msg = submitAnsweJson.dump();

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
