#pragma once
#include "IRequestHandler.h"
#include "requestHandlerFactory.h"

#define REMOVAL_SUCESS 1

class GameRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler(RequestHandlerFactory& f, LoggedUser& u, Room& r, RoomManager& rm);
	virtual bool isRequestRelevant(RequestInfo& inf);
	virtual RequestResult handleRequest(RequestInfo& inf);

private:
	RequestResult leaveRoom(RequestInfo);
	RequestResult getRoomState(RequestInfo);

	Room& m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

};