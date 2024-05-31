using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/*
struct LoginRequest
{
public:
	std::string username;
	std::string password;
}; 

struct SignupRequest
{
public:
	std::string username;
	std::string password;
	std::string email;
};

struct GetPlayersInRoomRequest
{
public:
	unsigned int roomId;
};

struct JoinRoomRequest
{
public:
	unsigned int roomId;
};

struct CreateRoomRequest
{
public:
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int anwerTimeout;
};

 */

namespace Requests
{
    public enum msgCodes
    {
        ERR = 0,
        SIGNUP,
        LOGIN,
        SIGNOUT,
        GET_ROOM,
        GET_PLAYERS,
        JOIN_ROOM,
        CREATE_ROOM,
        HIGH_SCORE,
        PERSONAL_STATS
    };

    public class LoginRequest
    {
        public string username { get; set; }
        public string password { get; set; }
    }

    public class SignupRequest
    {
        public string username { get; set; }
        public string password { get; set; }
        public string email { get; set; }
    }
}
