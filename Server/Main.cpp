#include "Server.h"
#include <iostream>
#include "LoginManager.h"


int main()
{
	try
	{
		/*
		//run server.
		Server server;
		server.Run();
		*/
		LoginManager lm;
		std::cout << lm.signup("Maria", "mrmrmr", "maria.h@hmail.com") << " "; // should be: 1
		std::cout << lm.signup("Natasha123", "mrmrmr", "maria.h@hmail.com") << " "; // should be: 0
		std::cout << lm.login("barnie", "barnn") << " "; // should be: -1
		std::cout << lm.login("Natasha123", "wrong_password") << " ";; // should be: 0
		std::cout << lm.login("Elirans", "eliran_t_best") << " ";; // should be: 1
		std::cout << lm.logout("Maria") << " ";; // should be: 1
		std::cout << lm.logout("gani") << " ";; // should be: 0
	}
	catch (std::exception& e)
	{
		std::cout << "An error occured: " << std::endl << e.what() << std::endl;
	}

	return 0;
}
