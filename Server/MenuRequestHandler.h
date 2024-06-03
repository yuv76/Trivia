#pragma once

#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"

#define ROOMS_FOUND 1
#define NO_ROOMS 0

#define USER_ADDED_SUCESSFULLY 1
#define USER_NOT_ADDED 0
#define ROOM_FULL -1

#define ROOM_CREATED_SUCESSFULLY 1
#define ROOM_CREATION_ERROR 0
#define ROOM_ALREADY_EXISTS -1

#define STATS_SUCCESS 1
#define STATS_ERROR 0

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory& r, LoggedUser lu);

	virtual bool isRequestRelevant(RequestInfo& inf);
	virtual RequestResult handleRequest(RequestInfo& inf);
private:
	RequestResult signout(RequestInfo inf);
	RequestResult getRooms(RequestInfo info);
	RequestResult getPlayersInRoom(RequestInfo info);
	RequestResult getPersonalStats(RequestInfo info);
	RequestResult getHighScore(RequestInfo info);
	RequestResult joinRoom(RequestInfo info);
	RequestResult createRoom(RequestInfo info);

	LoggedUser m_user;
	RequestHandlerFactory& m_handlerFactory;
};
