using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Responses
{
    public class SignupResponse
    {
        public const int SIGNUP_FAIL = 0;
        public const int SIGNUP_SUCCESS = 1;
        public uint status;
    };

    public class LoginResponse
    {   
        public const int LOGIN_F_WRONG_PASS = 0;
        public const int LOGIN_SUCCESS = 1;
        public const int LOGIN_F_NO_USER = 2;
        public const int LOGIN_F_CONNECTED_ALREADY = 3;
        public const int LOGIN_F_CONNECTION_ERROR = -4;
        public uint status;
    };

    public struct ErrorResponse
    {
        string message;
    };

    public struct LogoutResponse
    {
        public const int LOGOUT_FAIL = 0;
        public const int LOGOUT_SUCCESS = 1;
        uint status;
    };

    public struct GetRoomsResponse
    {
        public const int GET_ROOMS_FAIL = 0;
        public const int GET_ROOMS_SUCCESS = 1;
        uint status;
    };

    public struct GetPlayersInRoomResponse
    {
        public const int GET_PLAYERS_SUCCESS = 1;
        public const int GET_PLAYERS_FAIL = 0;
    };

    public struct GetHighScoreResponse
    {
        public const int HIGH_SCORES_FAIL = 0;
        public const int HIGH_SCORES_SUCCESS = 1;
        uint status;
    };

    public struct GetPersonalStatsResponse
    {
        public const int PERSONAL_STATS_FAIL = 0;
        public const int PERSONAL_STATS_SUCESS = 1;
        uint status;
    };

    public struct JoinRoomResponse
    {
        public const int JOIN_ROOM_FAIL = 0;
        public const int JOIN_ROOM_SUCCESS = 1;
        public const int ROOM_FULL = -1;
        uint status;
    };

    public struct CreateRoomResponse
    {
        public const int CREATE_ROOM_FAIL = 0;
        public const int CREATE_ROOM_SUCESS_ID = 1;
        public const int ROOM_EXISTS = -1;
        uint status;
    };

}
