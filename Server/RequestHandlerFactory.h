#pragma once

#include "SqliteDatabase.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"

class LoginRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* db);
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);
	LoginManager& getLoginManager();
	RoomManager& getRoomManager();

private:
	LoginManager m_loginManager;
	RoomManager m_roomManager;

	IDatabase* m_database;

};
