#include "Server.h"
#include <iostream>


int main()
{
	try
	{
		//run server.
		Server server;
		server.Run();
	}
	catch (std::exception& e)
	{
		std::cout << "An error occured: " << std::endl << e.what() << std::endl;
	}

	return 0;
}
