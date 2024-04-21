#pragma once
#include "IRequestHandler.h"
#include <vector>
#include <string>

class LoginRequestHandler : public IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo inf);
	virtual RequestResult handleRequest(RequestInfo inf);

//private:
	//static int binaryToDecimal(int n);
};