#pragma once
#include "RoomData.h"
#include "LoggedUser.h"
#include <vector>
#include <string>

class Room
{
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
public:
	Room(RoomData data, LoggedUser creator);
	void addUser(LoggedUser newMember);
	void removeUser(LoggedUser toKick);
	std::vector<std::string> getAllUsers();
	unsigned int isActive();
	RoomData getRoomData();
};