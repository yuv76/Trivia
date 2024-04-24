#include "LoginRequestHandler.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

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
	json result;
	if (inf.RequestId == LOGIN)
	{
		//perform the message
		res = this->login(inf);
		res.newHandler; // will be decided in a few minuetes.
	}
	else //sign up
	{
		SignupRequest log = JsonRequestPacketDeserializer::deserializeSignUpRequest(inf.buffer);
		SignupResponse s;
		
		//perform the request
		res = this->signup(inf);
		res.newHandler; // 

		s.status = 1;
		buffer = JsonResponsePacketSerializer::serializeSignUpResponse(s);
		res.response = buffer;
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
	buffer = JsonResponsePacketSerializer::serializeLoginResponse(l);
	rqRs.response = buffer;

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
	buffer = JsonResponsePacketSerializer::serializeSignUpResponse(s);
	rqRs.response = buffer;

	return rqRs;
}


/*
// Function to convert binary 
// to decimal 
int LoginRequestHandler::binaryToDecimal(int n)
{
	int num = n;
	int dec_value = 0;

	// Initializing base value to 
	// 1, i.e 2^0 
	int base = 1;

	int temp = num;
	while (temp) {
		int last_digit = temp % 10;
		temp = temp / 10;
		dec_value += last_digit * base;
		base = base * 2;
	}

	return dec_value;
}*/