#include "RequestHandlerFactory.h"

/*
C'tor for RequestHandlerFactory.
in: a database pointer.
*/
RequestHandlerFactory::RequestHandlerFactory(IDatabase* db) :
	m_database(db), m_loginManager(db), m_statisticsManager(db), m_gameManager(db)
{}

/*
creates a new LoginRequestHandler.
in: none.
out: a pointer to the login request handler.
*/
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	LoginRequestHandler* lgRqHr = new LoginRequestHandler(*this);
	return lgRqHr;
}

/*
returns the login manager.
in: none.
out: a LoginManager object.
*/
LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}

/*
creates a menu request handler for a given user.
in: the logged user to create the handler for, as a LoggedUser struct.
out: the newly created menu request handler's pointer.
*/
MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
	MenuRequestHandler* mnuRqHr = new MenuRequestHandler(*this, user);
	return mnuRqHr;
}

/*
returns the room manager.
in: none.
out: a reference to a room manager object.
*/
RoomManager& RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}

/*
returns the statistics manager.
in: none.
out: a reference to a StatisticsManager object.
*/
StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_statisticsManager;
}

/*
returns the game manager.
in: none.
out: a reference to a GameManager object.
*/
GameManager& RequestHandlerFactory::getGameManager()
{
	return this->m_gameManager;
}

/*
creates a room admin request handler for a given user owning a given room.
in: the room as a room object and the logged user to create the handler for, as a LoggedUser struct.
out: the newly created room admin request handler's pointer.
*/
RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser user, Room& room)
{
	RoomAdminRequestHandler* newRoomAdminRH = new RoomAdminRequestHandler(*this,user, room, this->m_roomManager);
	return newRoomAdminRH;
}

/*
creates a room member request handler for a given user.
in: the logged user to create the handler for, as a LoggedUser struct. the room the user is in as a room object.
out: the newly created room member request handler's pointer.
*/
RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser user, Room& room)
{
	RoomMemberRequestHandler* newRoomMemberRH = new RoomMemberRequestHandler(*this, user, room, this->getRoomManager());
	return newRoomMemberRH;
}

/*
creates a game request handler for a given user.
in: the logged user to create the handler for, as a LoggedUser struct.
out: the newly created game manager request handler's pointer.
*/
GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(LoggedUser user)
{
	GameRequestHandler* newGameManagerRH = new GameRequestHandler(*this, user, this->getGameManager());
	return newGameManagerRH;
}
