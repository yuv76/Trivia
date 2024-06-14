#include "LoginRequestHandler.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

/*
C'tor for login request handler.
in: a RequestHandlerFactory reference.
*/
LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& r) :
	m_handlerFactory(r)
{}

/*
checks if a given request is relevant for the class (login or signup).//at least i think signup..
in: a RequestInfo struct containing the type of the request.
out: true if relevant, false otherwise.
*/
bool LoginRequestHandler::isRequestRelevant(RequestInfo& inf)
{
	bool relevant = false;
	if (inf.RequestId == LOGIN || inf.RequestId == SIGNUP)
	{
		relevant = true;
	}
	return relevant;
}

/*
handles a login or signup request, make the response for it.
in: a RequestInfo struct containing the request details.
out: RequestResult struct containing the result details.
*/
RequestResult LoginRequestHandler::handleRequest(RequestInfo& inf)
{
	std::vector<std::uint8_t> buffer;
	RequestResult res;
	if (inf.RequestId == LOGIN)
	{
		//perform the message
		res = this->login(inf);
	}
	else //sign up
	{
		//perform the request
		res = this->signup(inf);
	}
	return res;
}

/*
Logs in a user according to its request.
in: request info struct.
out: request result struct.
*/
RequestResult LoginRequestHandler::login(RequestInfo inf)
{
	int status = 0;
	int res = 0;
	LoginResponse l;
	RequestResult rqRs;
	std::vector<std::uint8_t> buffer;

	LoginManager& lgnMgr = this->m_handlerFactory.getLoginManager();

	LoginRequest lgn = JsonRequestPacketDeserializer::deserializeLoginRequest(inf.buffer);
	status = lgnMgr.login(lgn.username, lgn.password);
	l.status = status;
	buffer = JsonResponsePacketSerializer::serializeResponse(l);
	rqRs.response = buffer;

	if (status == PASSWORDS_DONT_MATCH || status == USER_NOT_EXIST || status == USER_ALREADY_CONNECTED_CODE)
	{
		// failed - stay in login state
		rqRs.newHandler = this->m_handlerFactory.createLoginRequestHandler();
	}
	else // succesfull - move on to menu
	{
		rqRs.newHandler = this->m_handlerFactory.createMenuRequestHandler(LoggedUser(lgn.username));
	}

	return rqRs;
}

/*
signs up a new user according to its request.
in: request info struct containing the signup message.
out: request result struct.
*/
RequestResult LoginRequestHandler::signup(RequestInfo inf)
{
	int status = 0;
	int res = 0;
	SignupResponse s;
	RequestResult rqRs;
	std::vector<std::uint8_t> buffer;

	LoginManager& lgnMgr = this->m_handlerFactory.getLoginManager();

	SignupRequest sig = JsonRequestPacketDeserializer::deserializeSignUpRequest(inf.buffer);
	status = lgnMgr.signup(sig.username, sig.password, sig.email);
	s.status = status;
	buffer = JsonResponsePacketSerializer::serializeResponse(s);
	rqRs.response = buffer;

	if (status)
	{
		// failed - stay in login state
		rqRs.newHandler = this->m_handlerFactory.createLoginRequestHandler();
	}
	else // succesfull - move on to menu
	{
		rqRs.newHandler = this->m_handlerFactory.createMenuRequestHandler(LoggedUser(sig.username));
	}

	return rqRs;
}
