#pragma once
#include "RoomData.h"
#include "Responses.h"
#include "LoggedUser.h"
#include <vector>
#include <string>

#define LOBBY -1;

class Room
{
private:
	int _gameId;
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
public:
	//C'tors
	Room(RoomData data, LoggedUser creator);

	void addUser(LoggedUser newMember);
	void removeUser(LoggedUser toKick);
	std::vector<std::string> getAllUsers();
	std::vector<LoggedUser> getUsers();
	unsigned int isActive();
	void SetActiveState(unsigned int act);
	RoomData getRoomData();
	std::vector<std::string> getPlayersInRoomNames();
	GetRoomStateResponse getState();
	void updateGameID(int id);
	int getGameID() const;
};