#pragma once

#include "IRequestHandler.h"

class MenuRequestHandler : public IRequestHandler
{
	virtual bool isRequestRelevant(RequestInfo& inf);
	virtual RequestResult handleRequest(RequestInfo& inf);
};
