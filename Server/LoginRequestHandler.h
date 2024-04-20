#pragma once
#include "IRequestHandler.h"
#include "Requests.h"
#include <vector>
#include <string>

struct RequestInfo
{
	int msgCode;
	int msgTime;
	std::vector<std::string> msgContant;
};


class LoginRequestHandler : public IRequestHandler
{
	static bool isRequestRelevant(int msgCode);
	static RequestInfo handleRequest(RequestInfo info);


private:
	static int binaryToDecimal(int n);
};