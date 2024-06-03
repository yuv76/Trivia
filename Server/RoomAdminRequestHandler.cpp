#include "RoomAdminRequestHandler.h"

/*
C'tor for room admin request handler.
in: request handler factory, logged user, room and room manager references.
*/
RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& f, LoggedUser& u, Room& r, RoomManager& rm) :
	m_room(r), m_user(u), m_handlerFactory(f), m_roomManager(rm)
{}

/*
checks if a request is relevant for the room admin state.
in: the request's information.
out: true if relevant, false otherwise.
*/
bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo& inf)
{
	bool relevant = false;
	if (inf.RequestId == CLOSE_ROOM || inf.RequestId == START_GAME || inf.RequestId == GET_ROOM_STATE)
	{
		relevant = true;
	}
	return relevant;
}

/*

*/
RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo& inf)
{
	std::vector<std::uint8_t> buffer;
	RequestResult res;
	if (inf.RequestId == CLOSE_ROOM)
	{
		//perform the message
		res = this->closeRoom(inf);
	}
	else if(inf.RequestId == START_GAME)
	{
		//perform the request
		res = this->startGame(inf);
	}
	else // get room state
	{
		res = this->getRoomState(inf);
	}
	return res;
}

/*
creates the response for close room request.
in: the request's info.
out: the request's result.
*/
RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo)
{
	this->m_roomManager.deleteRoom(this->m_room.getRoomData().id);
	//send the message for all the other players.
}

/*
creates the response for start game request.
in: the request's info.
out: the request's result.
*/
RequestResult RoomAdminRequestHandler::startGame(RequestInfo)
{
	//send game start to all players.
}

/*
creates the response for get room state request.
in: the request's info.
out: the request's result.
*/
RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo)
{
	std::vector<std::uint8_t> buffer;
	RequestResult rqRs;
	GetRoomStateResponse resp = this->m_room.getState();

	buffer = JsonResponsePacketSerializer::serializeResponse(resp);

	rqRs.response = buffer;
	rqRs.newHandler = this->m_handlerFactory.createRoomAdminRequestHandler(this->m_user, this->m_room); //stay in admin state.

	return rqRs;
}
