#pragma once
#include "Room.h"
#include <map>
#include <mutex>

#define NO_STATE -1

class RoomManager
{
private:
	std::map<int, Room> m_rooms;
	std::mutex _mtx;
	std::unique_lock<std::mutex> _lck;

public:
	void createRoom(LoggedUser l, RoomData rd);
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	std::vector<RoomData> getRooms();
	Room& getRoom(int ID);
	int nextId();
	bool roomExists(std::string name);
};