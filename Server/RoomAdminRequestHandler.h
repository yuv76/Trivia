#pragma once
#include "IRequestHandler.h"
#include "requestHandlerFactory.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(RequestHandlerFactory& f, LoggedUser& u, Room& r, RoomManager& rm);
	virtual bool isRequestRelevant(RequestInfo& inf);
	virtual RequestResult handleRequest(RequestInfo& inf);

private:
	RequestResult closeRoom(RequestInfo);
	RequestResult startGame(RequestInfo);
	RequestResult getRoomState(RequestInfo);

	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

};