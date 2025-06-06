#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <map>
#include <mutex>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"

#define PORT 9090
#define BUFFER_SIZE 1024

class Communicator
{
public:
	Communicator(RequestHandlerFactory& fact);
	~Communicator();
	void startHandleRequests();
	
private:
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);
	void sendToClient(SOCKET clientSocket, RequestResult r);
	std::atomic<bool> _stopListening;
	std::mutex _ctSc;
	RequestHandlerFactory& m_handlerFactory;
};

