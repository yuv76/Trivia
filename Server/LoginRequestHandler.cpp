#include "LoginRequestHandler.h"


 bool LoginRequestHandler::isRequestRelevant(int msgCode)
{
	 // if the code is not for a login return false.
	 if (binaryToDecimal(msgCode) != 2)
		 return false;
	 return true;
}

RequestInfo LoginRequestHandler::handleRequest(RequestInfo info)
{

}


// Function to convert binary 
// to decimal 
int LoginRequestHandler::binaryToDecimal(int n)
{
	int num = n;
	int dec_value = 0;

	// Initializing base value to 
	// 1, i.e 2^0 
	int base = 1;

	int temp = num;
	while (temp) {
		int last_digit = temp % 10;
		temp = temp / 10;
		dec_value += last_digit * base;
		base = base * 2;
	}

	return dec_value;
}