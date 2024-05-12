#pragma once
#include "Room.h"
#include <map>

#define NO_STATE -1

class RoomManager
{
private:
	std::map<int, Room> m_rooms;
public:
	void createRoom(LoggedUser l, RoomData rd);
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	std::vector<RoomData> getRooms();
	Room& getRoom(int ID);
};