#include "Server.h"
#include <exception>
#include <iostream>


Server::Server()
{
	this->_n = 0;
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_listen == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}

}

Server::~Server()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(this->_listen);
		auto i = this->_serverSocket.begin();
		for (i; i != this->_serverSocket.end(); i++)
		{
			if (*i != INVALID_SOCKET)
			{
				closesocket(*i);
			}
		}
	}
	catch (...) {}
}

void Server::connectClients(int port)
{
	int n = 0; //number of user sockets.

	struct sockaddr_in sa = { 0 };
	std::cout << "Starting..." << std::endl;
	sa.sin_port = htons(port);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;
	/*
	accepting client...
	*/
	this->_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->_listen == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}
	// Connects between the socket and the configuration (port and etc..)
	if (bind(this->_listen, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - bind");
	}
	std::cout << "binded" << std::endl;
	// Start listening for incoming requests of clients
	if (listen(this->_listen, SOMAXCONN) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - listen");
	}
	std::cout << "listening..." << std::endl;

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		std::cout << "Waiting for client connection request" << std::endl;
		acceptClient();
	}
}


void Server::acceptClient()
{
	while (true)
	{
		// this accepts the client and create a specific socket from server to this client
		// the process will not continue until a client connects to the server
		this->_serverSocket.push_back(accept(this->_listen, NULL, NULL));
		if (this->_listen == INVALID_SOCKET)
		{
			throw std::exception(__FUNCTION__);
		}

		std::cout << "Client accepted" << std::endl;
		// the function that handle the conversation with the client
		std::thread tempThread(&Server::clientHandler, this, this->_serverSocket[this->_n]);
		tempThread.detach();
		this->_n++;
	}
}

void Server::clientHandler(SOCKET clientSocket)
{
	
}
