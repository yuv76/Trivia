using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Responses
{
    public class SignupResponse
    {
        public const uint SIGNUP_FAIL = 0;
        public const uint SIGNUP_SUCCESS = 1;
        public uint status;
    };

    public class LoginResponse
    {   
        public const uint LOGIN_F_WRONG_PASS = 0;
        public const uint LOGIN_SUCCESS = 1;
        public const uint LOGIN_F_NO_USER = 2;
        public const uint LOGIN_F_CONNECTED_ALREADY = 3;
        public const uint LOGIN_F_CONNECTION_ERROR = 4;
        public uint status;
    };

    public struct ErrorResponse
    {
        string message;
    };

    public struct LogoutResponse
    {
        public const uint LOGOUT_FAIL = 0;
        public const uint LOGOUT_SUCCESS = 1;
        uint status;
    };

    public struct GetRoomsResponse
    {
        public const uint GET_ROOMS_FAIL = 0;
        public const uint GET_ROOMS_SUCCESS = 1;
        uint status;
        //std::vector<RoomData> rooms;
    };

    public struct GetPlayersInRoomResponse
    {
        //std::vector<std::string> players;
    };

    public struct GetHighScoreResponse
    {
        public const uint HIGH_SCORES_FAIL = 0;
        public const uint HIGH_SCORES_SUCCESS = 1;
        uint status;
        //std::vector<std::string> statistics;
    };

    public struct GetPersonalStatsResponse
    {
        public const uint PERSONAL_STATS_FAIL = 0;
        public const uint PERSONAL_STATS_SUCESS = 1;
        uint status;
        //std::vector<std::string> statistics;
    };

    public struct JoinRoomResponse
    {
        public const uint JOIN_ROOM_FAIL = 0;
        public const uint JOIN_ROOM_SUCCESS = 1;
        uint status;
    };

    public struct CreateRoomResponse
    {
        public const uint CREATE_ROOM_FAIL = 0;
        public const uint CREATE_ROOM_SUCESS = 1;
        uint status;
    };

}
