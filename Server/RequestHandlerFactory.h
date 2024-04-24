#pragma once
#include "SqliteDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"

class RequestHandlerFactory
{
public:
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();

private:
	LoginManager m_loginManager;
	IDatabase* m_database;

};