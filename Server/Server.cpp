#include "Server.h"
#include "Communicator.h"
#include <exception>
#include <iostream>
#include <WinSock2.h>

/*
Server - Constructor.
parameter - has none.
return value - has none.
*/
Server::Server() :
	m_database(new SqliteDatabase), m_handlerFactory(m_database), _communicator(m_handlerFactory)
{
	//m_database->addNewQuestionsToDb(NUM_OF_QUESTIONS_TO_ADD);
}

/*
Server - Destructor.
parameter - has none.
return value - has none.
*/
Server::~Server()
{
	this->m_database->close();
	delete this->m_database;
}

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