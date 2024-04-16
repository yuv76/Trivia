#include "Server.h"
#include <iostream>


int main()
{
	try
	{
		bool exit = false;
		std::string input = "";
		Server server;
		//server.connectClients(9090);
		std::thread connect_clients_thread(&Server::connectClients, &server, 9090);
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
	system("PAUSE");

	return 0;
}