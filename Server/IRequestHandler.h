#pragma once
#include <vector>
#include "Requests.h"

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo inf) = 0;
	virtual RequestResult handleRequest(RequestInfo inf) = 0;
};

struct RequestResult
{
	std::vector<std::uint8_t> response;
	IRequestHandler* newHandler;
};

struct RequestInfo
{
	msgCodes RequestId;
	std::time_t receivalTime;
	std::vector<std::uint8_t> buffer;
};