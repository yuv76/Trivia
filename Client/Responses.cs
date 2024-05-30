using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Responses
{
    public class SignupResponse
    {
        public uint status;
    };

    public class LoginResponse
    {
        public const int LOGIN_SUCCESS = 1;
        public uint status;
    };

    public struct ErrorResponse
    {
        string message;
    };

    public struct LogoutResponse
    {
        uint status;
    };

    public struct GetRoomsResponse
    {
        uint status;
        //std::vector<RoomData> rooms;
    };

    public struct GetPlayersInRoomResponse
    {
        //std::vector<std::string> players;
    };

    public struct getHighScoreResponse
    {
        uint status;
        //std::vector<std::string> statistics;
    };

    public struct getPersonalStatsResponse
    {
        uint status;
        //std::vector<std::string> statistics;
    };

    public struct JoinRoomResponse
    {
        uint status;
    };

    public struct CreateRoomResponse
    {
        uint status;
    };

}
