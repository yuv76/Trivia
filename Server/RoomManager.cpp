#include "RoomManager.h"

/*
creates a new room.
in: the user who creates the room, the room data.
out: none.
*/
void RoomManager::createRoom(LoggedUser l, RoomData rd)
{
	Room newRoom(rd, l);
	_lck = std::unique_lock<std::mutex>(this->_mtx);
	this->m_rooms.insert(std::make_pair(rd.id, newRoom));
	_lck.unlock();

}

/*
deletes a room given its id.
in: the room to delete's id.
out: none.
*/
void RoomManager::deleteRoom(int ID)
{
	_lck = std::unique_lock<std::mutex>(this->_mtx);
	this->m_rooms.erase(ID);
	_lck.unlock();
}

/*
gets room state (if active) according to its id.
in: the room to get its state's id.
out: the room's state.
*/
unsigned int RoomManager::getRoomState(int ID)
{
	if (this->m_rooms.find(ID) != this->m_rooms.end())
	{
		return this->m_rooms.at(ID).isActive();
	}
	return NO_STATE;

}

/*
gets a vector with data of all rooms currently on the server that are open to join to.
in: none.
out: an std vector with every availabe room's data.
*/
std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> roomDatas;

	auto i = this->m_rooms.begin();
	for (i; i != this->m_rooms.end(); i++)
	{
		_lck = std::unique_lock<std::mutex>(this->_mtx);
		if (i->second.isActive() == ROOM_LOBY_STATE)
		{
			roomDatas.push_back(i->second.getRoomData());
		}
		_lck.unlock();
	}

	return roomDatas;
}

/*
returns a room by its id.
in: the id (int).
out: the room itself (a reference).
*/
Room& RoomManager::getRoom(int ID)
{
	_lck = std::unique_lock<std::mutex>(this->_mtx);
	if (this->m_rooms.find(ID) != this->m_rooms.end()) // if key exists.
	{
		_lck.unlock();
		return this->m_rooms.find(ID)->second;
	}
	_lck.unlock();
	throw std::exception("Invalid Room ID.");
}

/*
gets the next available room id.
in: none.
out: the unused id.
*/
int RoomManager::nextId()
{
	int id = 0;
	_lck = std::unique_lock<std::mutex>(this->_mtx);
	if (this->m_rooms.empty())
	{ 
		//first room
		id = 1;
	}
	else
	{
		//the map is sorted by increased oredr, so its last position will be its biggest key.
		id = this->m_rooms.rbegin()->first;
		//increase id by one to get the next unused id.
		id++;
	}
	_lck.unlock();
	return id;
}

/*
checks if a room with a given name exists.
in: the name to check.
out: true if exists, false otherwise.
*/
bool RoomManager::roomExists(std::string name)
{
	auto i = this->m_rooms.begin();
	for (i; i != this->m_rooms.end(); i++)
	{
		if (i->second.getRoomData().name == name && i->second.getRoomData().isActive != ROOM_CLOSED)
		{
			return true;
		}
	}
	return false;
}
