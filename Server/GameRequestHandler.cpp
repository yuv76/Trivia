#include "GameRequestHandler.h"



/*
C'tor for game request handler.
in: the handler factory, logged user, and game manager references.
*/
GameRequestHandler::GameRequestHandler(RequestHandlerFactory& f, LoggedUser& u, GameManager& gm, Game& g) :
	m_handlerFactory(f), m_user(u), m_gameManager(gm), m_game(g)
{}

/*
checks if a given request suits the game state.
in: the request's information.
out: true if relevant for the state, false otherwise.
*/
bool GameRequestHandler::isRequestRelevant(RequestInfo& inf)
{
	bool relevant = false;
	if (inf.RequestId == LEAVE_GAME || inf.RequestId == GET_QUESTION || inf.RequestId == SUBMIT_ANSWER || inf.RequestId == GET_GAME_RESULTS)
	{
		relevant = true;
	}
	return relevant;
}


/*
handles a request from a game, directing it to the choice and handling it.
in: the request's information.
out: the request's result.
*/
RequestResult GameRequestHandler::handleRequest(RequestInfo& inf)
{
	std::vector<std::uint8_t> buffer;
	RequestResult res;
	if (inf.RequestId == LEAVE_GAME)
	{
		//perform the message
		res = this->leaveGame(inf);
	}
	else if (inf.RequestId == GET_QUESTION)
	{
		//perform the request
		res = this->getQuestion(inf);
	}
	else if (inf.RequestId == SUBMIT_ANSWER)
	{
		//perform the request
		res = this->submitAnswer(inf);
	}
	else // get game results
	{
		//perform the request
		res = this->getGameResult(inf);
	}
	return res;
}

/*
creates the response for leave game request.
in: the request's info.
out: the request's result.
*/
RequestResult GameRequestHandler::leaveGame(RequestInfo)
{
	std::vector<std::uint8_t> buffer;
	LeaveGameResponse leave;
	RequestResult rqRs;

	this->m_game.removePlayer(this->m_user);
	leave.status = REMOVAL_SUCESS;

	buffer = JsonResponsePacketSerializer::serializeResponse(leave);

	rqRs.response = buffer;
	rqRs.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user); //move to menu

	return rqRs;
}

/*
creates the response for get question request.
in: the request's info.
out: the request's result.
*/
RequestResult GameRequestHandler::getQuestion(RequestInfo)
{
	std::vector<std::uint8_t> buffer;
	GetQuestionResponse question;
	RequestResult rqRs;

	Question resp = this->m_game.getQuestionForUser(this->m_user);
	if (resp.getQuestionId() == NO_MORE_QUESTIONS)
	{
		question.status = NO_MORE_QUESTIONS;
		this->m_game.setUserStatus(false, this->m_user); //sets status of user to not playing.
	}
	else
	{
		question.status = GOT_QUESTION;
	}
	question.question = resp.getQuestion();
	question.answers = resp.getPossibleAnswers();
	buffer = JsonResponsePacketSerializer::serializeResponse(question);

	rqRs.response = buffer;
	rqRs.newHandler = this->m_handlerFactory.createGameRequestHandler(this->m_user, this->m_game); // stay in current state.
	
	return rqRs;
}

/*
creates the response for submit answer request.
in: the request's info.
out: the request's result.
*/
RequestResult GameRequestHandler::submitAnswer(RequestInfo reqInf)
{
	std::vector<std::uint8_t> buffer;
	SubmitAnswerResponse answer;
	RequestResult rqRs;
	int correct = 0;

	SubmitAnswerRequest subAnsReq = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(reqInf.buffer);
	correct = this->m_game.submitAnswer(subAnsReq.answerId, this->m_user, subAnsReq.answerTime);
	answer.correctAnswerId = correct;
	answer.status = ANSWER_SUBMITTED;
	buffer = JsonResponsePacketSerializer::serializeResponse(answer);

	rqRs.response = buffer;
	rqRs.newHandler = this->m_handlerFactory.createGameRequestHandler(this->m_user, this->m_game);

	return rqRs;
}

/*
creates the response for get game result request.
in: the request's info.
out: the request's result.
*/
RequestResult GameRequestHandler::getGameResult(RequestInfo inf)
{
	std::vector<std::uint8_t> buffer;
	GetGameResultsResponse results;
	RequestResult rqRs;
	std::vector<std::pair<LoggedUser, GameData>> temp;
	PlayerResults result;

	temp = this->m_game.getData();
	auto i = temp.begin();
	for (i; i != temp.end(); i++)
	{
		if (!i->second.isActive) //only if user finished game, we want to
		{
			result.average = i->second.averangeAnswerTime;
			result.coorect = i->second.correctAnswerCount;
			result.username = i->first.getUsername();
			result.wrong = i->second.wrongAnswerCount;
			results.results.push_back(result);
		}
		else
		{
			result.username = i->first.getUsername();
			result.average = -1; //flag to determine the user is still playing.
			result.coorect = 0;
			result.wrong = 0;
			results.results.push_back(result);
		}
	}
	this->m_game.checkIfFinished();
	if (this->m_game.isActive())
	{
		results.status = GOT_UNFINAL_RESULT;
	}
	else
	{
		results.status = GOT_RESULT;
	}
	
	buffer = JsonResponsePacketSerializer::serializeResponse(results);

	rqRs.response = buffer;
	if (this->m_game.isActive())
	{
		rqRs.newHandler = this->m_handlerFactory.createGameRequestHandler(this->m_user, this->m_game); // stay in state.
	}
	else
	{
		rqRs.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);
		this->m_gameManager.deleteGame(this->m_game.getId());
	}

	return rqRs;
}
