#pragma once

#include <WinSock2.h>
#include <Windows.h>

#include <string>
#include <set>
#include <thread>
#include <queue>
#include <fstream>
#include <map>
#include <mutex>

#include "Communicator.h"


#define BUFF_SIZE 1024

#define NUM_OF_QUESTIONS_TO_ADD 10

class Server
{
public:
	Server();
	~Server();

	void Run();

private:

	IDatabase* m_database;
	RequestHandlerFactory m_handlerFactory;

	Communicator _communicator;
};

