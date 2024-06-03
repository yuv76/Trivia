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

*/
RequestResult closeRoom(RequestInfo)
{

}

/*

*/
RequestResult startGame(RequestInfo)
{

}

/*

*/
RequestResult getRoomState(RequestInfo)
{

}
