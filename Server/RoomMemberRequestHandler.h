#pragma once
#include "IRequestHandler.h"
#include "requestHandlerFactory.h"

class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(LoggedUser u, Room r);
	virtual bool isRequestRelevant(RequestInfo& inf);
	virtual RequestResult handleRequest(RequestInfo& inf);

private:
	RequestResult leaveRoom(RequestInfo);
	RequestResult getRoomState(RequestInfo);

	Room m_room;
	LoggedUser m_user;
	RoomManager&  m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

};