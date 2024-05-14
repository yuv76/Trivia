#include "RequestHandlerFactory.h"

/*
C'tor for RequestHandlerFactory.
in: a database pointer.
*/
RequestHandlerFactory::RequestHandlerFactory(IDatabase* db) :
	m_database(db), m_loginManager(db)
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