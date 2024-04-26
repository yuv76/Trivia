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
blank for now
*/
MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler()
{
	MenuRequestHandler l;
	return &l;
}