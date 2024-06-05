#include "RoomMemberRequestHandler.h"


/*
C'tor for room member request handler.
in: the handler factory, logged user, room and room manager references.
*/
RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& f, LoggedUser& u, Room& r, RoomManager& rm):
	m_handlerFactory(f), m_user(u), m_room(r), m_roomManager(rm)
{}

/*
checks if a given request suits the room member state.
in: the request's information.
out: true if relevant for the state, false otherwise.
*/
bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo& inf)
{
	bool relevant = false;
	if (inf.RequestId == LEAVE_ROOM || inf.RequestId == GET_ROOM_STATE)
	{
		relevant = true;
	}
	return relevant;
}

/*
handles a request from a Room member, directing it to the choice and handling it.
in: the request's information.
out: the request's result.
*/
RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo& inf)
{
	std::vector<std::uint8_t> buffer;
	RequestResult res;
	if (inf.RequestId == LEAVE_ROOM)
	{
		//perform the message
		res = this->leaveRoom(inf);
	}
	else // get room state
	{
		//perform the request
		res = this->getRoomState(inf);
	}
	return res;
}

/*
creates the response for leave room request.
in: the request's info.
out: the request's result.
*/
RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo)
{
	std::vector<std::uint8_t> buffer;
	LeaveRoomResponse leave;
	RequestResult rqRs;

	this->m_room.removeUser(this->m_user);
	leave.status = REMOVAL_SUCESS;

	buffer = JsonResponsePacketSerializer::serializeResponse(leave);

	rqRs.response = buffer;
	rqRs.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user); //move to menu

	return rqRs;
}

/*
creates the response for get room state request.
in: the request's info.
out: the request's result.
*/
RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo)
{
	std::vector<std::uint8_t> buffer;
	RequestResult rqRs;

	GetRoomStateResponse resp = this->m_room.getState();

	buffer = JsonResponsePacketSerializer::serializeResponse(resp);

	rqRs.response = buffer;
	rqRs.newHandler = this->m_handlerFactory.createRoomMemberRequestHandler(this->m_user, this->m_room); //stay in room member state.

	return rqRs;
}
