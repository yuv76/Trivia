#pragma once

#include "Requests.h"
#include <vector>
#include <string>

#define MSG_HEADER 5

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<std::uint8_t> buffer);
	static SignupRequest deserializeSignUpRequest(std::vector<std::uint8_t> buffer);

	static GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(std::vector<std::uint8_t> buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(std::vector<std::uint8_t> buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(std::vector<std::uint8_t> buffer);
	static SubmitAnswerRequest deserializeSubmitAnswerRequest(std::vector<std::uint8_t> buffer);
};
