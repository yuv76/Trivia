#include "Server.h"
#include <iostream>
#include "SqliteDatabase.h"


int main()
{
	try
	{
		/*
		//run server.
		Server server;
		server.Run();
		*/
		SqliteDatabase sd;
		sd.open();
		std::cout << sd.addNewUser("Natasha123", "natTheCat22", "natasha.cat4ever@hmail.com") << " "; // should be: 1
		std::cout << sd.addNewUser("Elirans", "eliran_t_best", "eliran.the.man@hmail.com") << " "; // should be: 1
		std::cout << sd.addNewUser("Natasha123", "sisma", "natasha.shichpool@hmail.com") << std::endl; // should be: "User with given name already exists."
		std::cout << sd.doesUserExist("Natasha123") << " " << sd.doesUserExist("eliyahool") << " " << sd.doesUserExist("Elirans") << " " << sd.doesUserExist("matillda") << std::endl; // should be: 1 0 1 0
		std::cout << sd.doesPasswordMatch("matillda", "ttt") << " " << sd.doesPasswordMatch("Natasha123", "wrong_pass") << " " << sd.doesPasswordMatch("Elirans", "eliran_t_best") << std::endl; // should be: 0 0 1

		sd.close();
	}
	catch (std::exception& e)
	{
		std::cout << "An error occured: " << std::endl << e.what() << std::endl;
	}

	return 0;
}
