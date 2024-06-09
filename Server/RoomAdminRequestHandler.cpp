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
handles a request for room admin state.
in: the request's info to handle.
out: the handled request's result.
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
	RequestResult rqRs;
	std::vector<std::uint8_t> buffer;
	CloseRoomResponse closeRsp;

	try
	{
		this->m_room.SetActiveState(ROOM_CLOSED);
		this->m_roomManager.getRoom(this->m_room.getRoomData().id).SetActiveState(ROOM_CLOSED);
		//will send game start to all players when they will get their next room update.
		closeRsp.status = ROOM_CLOSED_SUCCESSFULLY;
	}
	catch (...)
	{
		closeRsp.status = ROOM_CLOSE_FAIL;
	}
	buffer = JsonResponsePacketSerializer::serializeResponse(closeRsp);

	rqRs.response = buffer;
	rqRs.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user); // back to menu.

	return rqRs;
}

/*
creates the response for start game request.
in: the request's info.
out: the request's result.
*/
RequestResult RoomAdminRequestHandler::startGame(RequestInfo)
{
	RequestResult rqRs;
	std::vector<std::uint8_t> buffer;
	StartGameResponse stGResp;
	try
	{
		this->m_room.SetActiveState(GAME_STARTED_IN_ROOM);
		//will send game start to all players when they will get next room update.
		stGResp.status = GAME_STARTED_SUCESSFULY;
	}
	catch(...)
	{
		stGResp.status = GAME_START_FAIL;
	}
	buffer = JsonResponsePacketSerializer::serializeResponse(stGResp);

	rqRs.response = buffer;
	//rqRs.newHandler = this->m_handlerFactory.createRoomAdminRequestHandler(this->m_user, this->m_room); //stay in admin state.
	rqRs.newHandler = this->m_handlerFactory.createGameRequestHandler(this->m_user, this->m_handlerFactory.getGameManager().createGame(this->m_room)); //start room.

	return rqRs;
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
