#pragma once

#include "SqliteDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"

class LoginRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* db);
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();
	LoginManager& getLoginManager();

private:
	LoginManager m_loginManager;
	IDatabase* m_database;

};
