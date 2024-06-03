#include "Room.h"

/*
C'tor for room object.
in: the room's data, the room creator (a user).
*/
Room::Room(RoomData data, LoggedUser creator)
{
	this->m_metadata = data;
	this->m_users.push_back(creator);
}

/*
adds a new user to the room.
in: the new user.
out: none.
*/
void Room::addUser(LoggedUser newMember)
{
	this->m_users.push_back(newMember);
}

/*
removes a user from the room.
in: the user to kick.
out: none
*/
void Room::removeUser(LoggedUser toKick)
{
	auto i = this->m_users.begin();
	for (i; i != this->m_users.end(); i++)
	{
		if (*i == toKick)
		{
			this->m_users.erase(i); //might cause exception?
		}
	}
}

/*
gets a string vector with all logged users' names.
in: none.
out: a vector with the user names.
*/
std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> names;

	auto i = this->m_users.begin();
	for (i; i != this->m_users.end(); i++)
	{
		names.push_back(i->getUsername());
	}

	return names;
}

/*
returns if the room is active.
in: none.
out: the status of the room.
*/
unsigned int Room::isActive()
{
	return this->m_metadata.isActive;
}

/*
gets the room's data - a roomData object
in: none.
out: the room's data.
*/
RoomData Room::getRoomData()
{
	return this->m_metadata;
}

/*
returns an std vector with the names of the users logged to the room.
in: none.
out: the vector with the names.
*/
std::vector<std::string> Room::getPlayersInRoomNames()
{
	std::vector<std::string> players;

	auto i = this->m_users.begin();
	for (i; i != this->m_users.end(); i++)
	{
		players.push_back(i->getUsername());
	}

	return players;
}

/*
gets room's state into a get room state response struct.
in: none.
out: the getRoomStateResponse with the room's data.
*/
GetRoomStateResponse Room::getState()
{
	GetRoomStateResponse resp;

	//players from vector (comes from the room) into list.
	std::vector<std::string> playersVec = this->getAllUsers();
	std::list<std::string> playersLst(playersVec.begin(), playersVec.end());

	//add the room's data to the response.
	resp.AnswerCount = this->m_metadata.numOfQuestionsInGame;
	resp.answerTimeOut = this->m_metadata.timePerQuestion;
	resp.hasGameBegun = false;//#TODO
	resp.players = playersLst;
	resp.status = this->m_metadata.isActive;
}