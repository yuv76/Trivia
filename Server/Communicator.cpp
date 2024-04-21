#include "Communicator.h"
#include <iostream>
#include <sstream>

Communicator::Communicator()
{
	this->_stopListening.store(false);
	WSADATA wsa_data = { };
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
	{
		throw std::exception("WSAStartup Failed");
	}
	this->m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->m_serverSocket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}
}

Communicator::~Communicator()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		//closesocket(this->_listen);
		auto i = this->m_clients.begin();
		for (; i != this->m_clients.end(); i++)
		{
			if (i->first != INVALID_SOCKET)
			{
				closesocket(i->first);
			}
			delete i->second;
		}

		std::unique_lock<std::mutex> lck(this->_ctSc);

		this->_stopListening.store(true);
		closesocket(this->m_serverSocket);
		this->m_serverSocket = INVALID_SOCKET;
		lck.unlock();

		WSACleanup();
	}
	catch (std::exception &e) 
	{
		std::cout << "An error occured: " << e.what() << std::endl;
	}
}

void Communicator::startHandleRequests()
{
	int n = 0; //number of user sockets.

	struct sockaddr_in sa = { 0 };
	std::cout << "Starting..." << std::endl;
	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"
	/*
	accepting client...
	*/
	this->m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->m_serverSocket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}
	// Connects between the socket and the configuration (port and etc..)
	if (bind(this->m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - bind");
	}
	std::cout << "binded" << std::endl;
	// Start listening for incoming requests of clients
	if (listen(this->m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw std::exception(__FUNCTION__ " - listen");
	}
	std::cout << "listening..." << std::endl;

	// the main thread is only accepting clients 
	// and add then to the list of handlers
	std::cout << "Waiting for client connection request" << std::endl;
	this->bindAndListen();
}

void Communicator::bindAndListen()
{
	SOCKET tmp;
	while (!(this->_stopListening.load()))
	{
		// this accepts the client and create a specific socket from server to this client
		// the process will not continue until a client connects to the server

		if (!(this->_stopListening.load()))
		{
			if (this->m_serverSocket == INVALID_SOCKET)
			{
				throw std::exception(__FUNCTION__);
			}
			tmp = accept(this->m_serverSocket, NULL, NULL);
			this->m_clients[tmp] = new IRequestHandler();


			std::cout << "Client accepted" << std::endl;
			// the function that handle the conversation with the client
			std::thread tempThread(&Communicator::handleNewClient, this, tmp);
			tempThread.detach();
		}
	}
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	std::string message = "Hello";

	try
	{
		// sanding the first message - Hello message
		const char* data = message.c_str();

		if (send(clientSocket, data, message.size(), 0) == INVALID_SOCKET)
		{
			throw std::exception("Error while sending message to client");
		}

		// receive the client message
		char* clientData = new char[BYTESNUM + 1];
		int res = recv(clientSocket, clientData, BYTESNUM, 0);

		if (res == INVALID_SOCKET)
		{
			std::string s = "Error while recieving from socket: ";
			s += std::to_string(clientSocket);
			throw std::exception(s.c_str());
		}

		clientData[BYTESNUM] = 0;

		std::string clientMessage(clientData);

		// if sent a message thats not Hello
		if (clientMessage.substr(0, BYTESNUM) != "Hello")
		{
			throw("Protocol Exception");
		}
		// print the Hello message
		else
		{
			std::cout << clientMessage << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Error - " << e.what() << std::endl;
		closesocket(clientSocket);
	}
}