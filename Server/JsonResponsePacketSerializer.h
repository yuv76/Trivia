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

	std::vector<std::uint8_t> serializeResponse(LogoutResponse log);
	std::vector<std::uint8_t> serializeResponse(GetRoomsResponse getR);
	std::vector<std::uint8_t> serializeResponse(GetPlayersInRoomResponse getP);
	std::vector<std::uint8_t> serializeResponse(JoinRoomResponse join);
	std::vector<std::uint8_t> serializeResponse(CreateRoomResponse crea);
	std::vector<std::uint8_t> serializeResponse(getHighScoreResponse high);
	std::vector<std::uint8_t> serializeResponse(getPersonalStatsResponse high);
};
