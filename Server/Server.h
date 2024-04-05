#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <string>
#include <set>
#include <thread>
#include <queue>
#include <fstream>
#include <condition_variable>

#define BUFF_SIZE 1024

static std::mutex m;
static std::mutex messagesMutex;
static std::mutex userListMutex;

class Server
{
public:
	Server();
	~Server();
	
	void connectClients(int port);
	std::set<std::string> _connectedUsers;

private:

	void acceptClient();
	void clientHandler(SOCKET clientSocket);
	int _n; //number of sockets.
	std::vector<SOCKET> _serverSocket;
	SOCKET _listen;
};
