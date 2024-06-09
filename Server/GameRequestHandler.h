#pragma once
#include "IRequestHandler.h"
#include "requestHandlerFactory.h"

#define REMOVAL_SUCESS 1

class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(RequestHandlerFactory& f, LoggedUser& u, GameManager& rm);
	virtual bool isRequestRelevant(RequestInfo& inf);
	virtual RequestResult handleRequest(RequestInfo& inf);

private:
	LoggedUser m_user;
	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFactory;

};