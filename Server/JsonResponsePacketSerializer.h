#pragma once

#include "Responses.h"
#include "Requests.h"
#include <vector>
#include <string>

class JsonResponsePacketSerializer
{
public:
	static std::vector<std::uint8_t> serializeResponse(ErrorResponse err);
	static std::vector<std::uint8_t> serializeResponse(LoginResponse log);
	static std::vector<std::uint8_t> serializeResponse(SignupResponse sig);

	static std::vector<std::uint8_t> serializeResponse(LogoutResponse log);
	static std::vector<std::uint8_t> serializeResponse(GetRoomsResponse getR);
	static std::vector<std::uint8_t> serializeResponse(GetPlayersInRoomResponse getP);
	static std::vector<std::uint8_t> serializeResponse(JoinRoomResponse join);
	static std::vector<std::uint8_t> serializeResponse(CreateRoomResponse crea);
	static std::vector<std::uint8_t> serializeResponse(getHighScoreResponse high);
	static std::vector<std::uint8_t> serializeResponse(getPersonalStatsResponse pers);
};
