#include "Server.h"
#include "Communicator.h"
#include <exception>
#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

/*
Server - Constructor.
parameter - has none.
return value - has none.
*/
Server::Server() :
	_communicator()
{}

/*
Server - Destructor.
parameter - has none.
return value - has none.
*/
Server::~Server()
{}

/*
connectClients - Connector, connects you to a client socket using acceptClient.
parameter - the port to listen to.
return value - has none.

void Server::connectClients(int port)
{
	int n = 0; //number of user sockets.

	struct sockaddr_in sa = { 0 };
	std::cout << "Starting..." << std::endl;
	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"
	/*
	accepting client...
	*/
/*
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

	// the main thread is only accepting clients 
	// and add then to the list of handlers
	std::cout << "Waiting for client connection request" << std::endl;
	acceptClient();
}*/

/*
acceptClient - accepts the new client sockets.
parameter - has none.
return value - has none.

void Server::acceptClient()
{
	while (!(this->_stopListening.load()))
	{
		// this accepts the client and create a specific socket from server to this client
		// the process will not continue until a client connects to the server
		
		if (!(this->_stopListening.load()))
		{
			if (this->_listen == INVALID_SOCKET)
			{
				throw std::exception(__FUNCTION__);
			}
			this->_serverSocket.push_back(accept(this->_listen, NULL, NULL));
			

			std::cout << "Client accepted" << std::endl;
			// the function that handle the conversation with the client
			std::thread tempThread(&Server::clientHandler, this, this->_serverSocket[this->_n]);
			tempThread.detach();
			this->_n++;
		}
	}
}*/

/*
clientHandler - gets the socket of the new client and listens to its messages, and sends the respnse.
parameter - the port to listen to.
return value - has none.

void Server::clientHandler(SOCKET clientSocket)
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
}*/


/*
Run - runs the Communicators startHandleRequests to connect .
parameter - has none.
return value - has none.
*/
void Server::Run()
{
	try
	{
		bool exit = false;
		std::string input = "";

		std::thread connect_clients_thread(&Communicator::startHandleRequests, &_communicator);
		connect_clients_thread.detach();

		while (!exit)
		{
			std::cout << "type 'EXIT' to quit" << std::endl;
			std::getline(std::cin, input);

			if (input == "EXIT")
			{
				exit = true; // Exit the loop if the user enters 'EXIT'
			}
		}
	}
	catch (std::exception& e)
	{
		std::cout << "An error occured: " << std::endl << e.what() << std::endl;
	}
}