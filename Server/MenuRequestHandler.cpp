#include "MenuRequestHandler.h"

/*
C'tor for menu request handler.
in: a RequestHandlerFactory reference.
*/
MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& r, LoggedUser lu) :
	m_handlerFactory(r), m_user(lu)
{}

/*
checks if a given request is relevant for menu handler.
in: the RequestInfo struct containing data on the request.
out: true if relevant, false otherwise.
*/
bool MenuRequestHandler::isRequestRelevant(RequestInfo& inf)
{
	bool relevant = false;
	//check if request is one of menu options:
	if (inf.RequestId == SIGNOUT || inf.RequestId == GET_ROOM 
		|| inf.RequestId == GET_PLAYERS || inf.RequestId == JOIN_ROOM 
		|| inf.RequestId == CREATE_ROOM || inf.RequestId == HIGH_SCORE 
		|| inf.RequestId == PERSONAL_STATS)
	{
		relevant = true;
	}
	return relevant;
}

/*

*/
RequestResult MenuRequestHandler::handleRequest(RequestInfo& inf)
{
	RequestResult r;
	return r;
}

/*
gets a logout request and logs current user out of the system.
in: the request information.
out: the result of the request in a RequestResult struct.
*/
RequestResult MenuRequestHandler::signout(RequestInfo inf)
{
	int status = 0;
	LogoutResponse l;
	RequestResult rqRs;
	std::vector<std::uint8_t> buffer;

	LoginManager& lgnMngr = this->m_handlerFactory.getLoginManager();

	status = lgnMngr.logout(this->m_user.getUsername());
	l.status = status;
	buffer = JsonResponsePacketSerializer::serializeResponse(l);
	rqRs.response = buffer;

	if (status)
	{
		// failed - stay in menu state
		rqRs.newHandler = this;
	}
	else // succesfull - move on to login (?) #TODO
	{
		rqRs.newHandler = this->m_handlerFactory.createLoginRequestHandler();
	}

	return rqRs;
}

/*
gets a request for rooms and returns its result.
in: the request's info, as a RequestInfo struct.
out: the request's result as a RequestResult struct.
*/
RequestResult MenuRequestHandler::getRooms(RequestInfo info)
{
	int status = 0;
	GetRoomsResponse r;
	RequestResult rqRs;
	std::vector<RoomData> rooms;
	std::vector<std::uint8_t> buffer;

	RoomManager& roomMngr = this->m_handlerFactory.getRoomManager();

	rooms = roomMngr.getRooms();
	if (rooms.empty())
	{
		status = NO_ROOMS;
	}
	else
	{
		status = ROOMS_FOUND;
	}

	r.status = status;
	buffer = JsonResponsePacketSerializer::serializeResponse(r);
	rqRs.response = buffer;

	// stay in menu state
	rqRs.newHandler = this;

	return rqRs;
}

/*
gets a get Players In Room request and returns its response.
in: the request;s information, a RequestInfo object.
out: the requests's result, a RequestResult object.
*/
RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo info)
{
	GetPlayersInRoomResponse p;
	RequestResult rqRs;
	std::vector<std::string> players;
	std::vector<std::uint8_t> buffer;

	GetPlayersInRoomRequest plyrRqst = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(info.buffer);

	RoomManager& roomMngr = this->m_handlerFactory.getRoomManager();

	players = roomMngr.getRoom(plyrRqst.roomId).getPlayersInRoomNames();
	p.players = players;

	buffer = JsonResponsePacketSerializer::serializeResponse(p);
	rqRs.response = buffer;

	// stay in menu state
	rqRs.newHandler = this;

	return rqRs;
}

/*

*/
RequestResult MenuRequestHandler::getPersonalStats(RequestInfo info)
{
	// ---
	RequestResult rr;
	return rr;
}

/*

*/
RequestResult MenuRequestHandler::getHighScore(RequestInfo info)
{
	RequestResult rr;
	return rr;
	// ---
}

/*
preforms a join room request.
in: a Request Info struct containing the request to create the response for.
out: the request's result.
*/
RequestResult MenuRequestHandler::joinRoom(RequestInfo info)
{
	JoinRoomResponse j;
	RequestResult rqRs;
	std::vector<std::uint8_t> buffer;

	JoinRoomRequest joinRqst = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer);

	RoomManager& roomMngr = this->m_handlerFactory.getRoomManager();

	try
	{
		Room addTo = roomMngr.getRoom(joinRqst.roomId);
		addTo.addUser(this->m_user);
		j.status = USER_ADDED_SUCESSFULLY;
	}
	catch (std::exception& e)
	{
		j.status = USER_NOT_ADDED;
	}

	buffer = JsonResponsePacketSerializer::serializeResponse(j);
	rqRs.response = buffer;

	// stay in menu state
	rqRs.newHandler = this;

	return rqRs;
}

/*
handles a create room response.
in: the request's info as a RequestInfo struct.
out: the request's result as a RequestResult struct.
*/
RequestResult MenuRequestHandler::createRoom(RequestInfo info)
{
	int lastId = 0;
	CreateRoomResponse c;
	RoomData newRoom;
	RequestResult rqRs;
	std::vector<std::uint8_t> buffer;

	CreateRoomRequest createRqst = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buffer);

	RoomManager& roomMngr = this->m_handlerFactory.getRoomManager();
	try
	{
		newRoom.maxPlayers = createRqst.maxUsers;
		newRoom.name = createRqst.roomName;
		newRoom.numOfQuestionsInGame = createRqst.questionCount;
		newRoom.timePerQuestion = createRqst.anwerTimeout;
		newRoom.isActive = 1; //couldnt find any declaration of active options #TODO
		
		lastId = this->m_handlerFactory.getRoomManager().nextId();
		newRoom.id = lastId;

		roomMngr.createRoom(this->m_user, newRoom);

		c.status = ROOM_CREATED_SUCESSFULLY;
	}
	catch (...)
	{
		c.status = ROOM_CREATION_ERROR;
	}

	buffer = JsonResponsePacketSerializer::serializeResponse(c);
	rqRs.response = buffer;

	// stay in menu state
	rqRs.newHandler = this;

	return rqRs;
}
