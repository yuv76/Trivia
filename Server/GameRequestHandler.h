#pragma once
#include "IRequestHandler.h"
#include "requestHandlerFactory.h"

#define REMOVAL_SUCESS 1

#define ANSWER_SUBMITTED 1

class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(RequestHandlerFactory& f, LoggedUser& u, GameManager& gm, Game& g);
	virtual bool isRequestRelevant(RequestInfo& inf);
	virtual RequestResult handleRequest(RequestInfo& inf);

private:
	RequestResult leaveGame(RequestInfo);
	RequestResult getQuestion(RequestInfo);
	RequestResult submitAnswer(RequestInfo reqInf);
	RequestResult getGameResult(RequestInfo inf);

	Game& m_game;
	LoggedUser m_user;
	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFactory;

};