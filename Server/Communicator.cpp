#include "Communicator.h"

#pragma comment(lib, "ws2_32.lib")


/*
communicator C'tor.
in: the request handle factory.
*/
Communicator::Communicator(RequestHandlerFactory& fact) :
	m_handlerFactory(fact)
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

/*
communicator D'tor.
*/
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
	catch (std::exception& e)
	{
		std::cout << "An error occured: " << e.what() << std::endl;
	}
}

/*
starts the listening for clients and binds them.
in: none.
out: none.
*/
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

/*
binds clients that are trying to connect to their thread.
in: none.
out: none.
*/
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
			this->m_clients[tmp] = new LoginRequestHandler(m_handlerFactory);


			std::cout << "Client accepted" << std::endl;
			// the function that handle the conversation with the client
			std::thread tempThread(&Communicator::handleNewClient, this, tmp);
			tempThread.detach();
		}
	}
}

/*
handles a client, gets a message and responds.
in: the socket with the client.
out: none.
*/
void Communicator::handleNewClient(SOCKET clientSocket)
{
	bool connected = true;
	try
	{
		while (m_clients[clientSocket] != nullptr)
		{
			//will be a loop later on.
			// receive the client message
			int len = 0, i = 0;
			char* tempCharRecv = new char[BUFFER_SIZE];
			//get time of start receiving
			std::time_t recvTime = time(0);
			//first get the length of the message about to come.
			recv(clientSocket, tempCharRecv, MSG_HEADER, 0);
			len = (tempCharRecv[1] << 24) | (tempCharRecv[2] << 16) | (tempCharRecv[3] << 8) | tempCharRecv[4]; // Index 0 is msg code, next 4 are length.

			std::vector<uint8_t> temp;// (len);
			std::vector<uint8_t> buffer;// (len + MSG_HEADER);
			std::vector<uint8_t> tempTemp(BUFFER_SIZE); // The temp for the temp
			//Add header to buffer.
			for (i = 0; i < MSG_HEADER; i++)
			{
				buffer.push_back(tempCharRecv[i]);
			}
			//if length is bigger than buffer size, scan it in parts (last scan will be less than 1024 and outside of loop).
			while (len > BUFFER_SIZE)
			{

				recv(clientSocket, tempCharRecv, BUFFER_SIZE, 0);
				std::copy(tempCharRecv, tempCharRecv + BUFFER_SIZE, tempTemp.begin());
				temp.insert(temp.end(), tempTemp.begin(), tempTemp.end()); // add tempTemp at end of main temp.
				len -= BUFFER_SIZE;
			}
			if (len > 0) //last scan (or first if length was smaller than 1024 in the first place)
			{
				std::vector<uint8_t> tempInLen(len);
				recv(clientSocket, tempCharRecv, len, 0);
				std::copy(tempCharRecv, tempCharRecv + len, tempInLen.begin());
				temp.insert(temp.end(), tempInLen.begin(), tempInLen.end()); //insert the length to temp so copying will be possible.
			}
			buffer.insert(buffer.end(), temp.begin(), temp.end()); // add temp at end of buffer

			RequestInfo info;
			info.buffer = buffer;
			info.receivalTime = recvTime;
			info.RequestId = (msgCodes)buffer[0];

			//IRequestHandler* l = this->m_handlerFactory.createLoginRequestHandler();
			
			RequestResult r;
			if (m_clients[clientSocket]->isRequestRelevant(info))
			{
				r = m_clients[clientSocket]->handleRequest(info);

				delete m_clients[clientSocket];

				m_clients[clientSocket] = r.newHandler;
			}
			else //error
			{
				
				
			}

			// sanding the response message to client.
			char* dataHeader = new char[5]; // have to send as char*.
			char* data = new char[r.response.size() - 5];
			std::copy(r.response.begin() + 5, r.response.end(), data);
			std::copy(r.response.begin(), r.response.begin() + 5, dataHeader);

			send(clientSocket, dataHeader, 5, 0);
			send(clientSocket, data, r.response.size() - 5, 0);
			/*
			while (m_clients[clientSocket] != nullptr)
			{
				info = { (msgCodes)buffer[0], recvTime,  buffer };
				if (m_clients[clientSocket]->isRequestRelevant(info))
				{
					RequestResult result = m_clients[clientSocket]->handleRequest(info);

					std::string response(result.response.begin(), result.response.end());
					// sanding the response message to client.
					char* data = new char[r.response.size()]; // have to send as char*.
					std::copy(r.response.begin(), r.response.end(), data);
					send(clientSocket, data, r.response.size(), 0);

					
				}
			}*/

			delete[] tempCharRecv;


		}
		closesocket(clientSocket);
		std::cout << "client disconnected" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error - " << e.what() << std::endl;
		closesocket(clientSocket);
	}
}
