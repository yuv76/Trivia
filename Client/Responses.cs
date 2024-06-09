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

    public struct GetRoomStateResponse
    {
        public const int GET_STATE_SUCESS = 1;
        public const int GET_STATE_FAILURE = 0;

        public const uint ROOM_CLOSED = 0;
        public const uint ROOM_LOBBY = 1;
        public const uint GAME_IN_PROGRESS = 2;
        public const uint CONNECTION_PROBLEM = 3;

        public List<string> players;
        public uint numOfQuestionsInGame;
        public double timePerQuestion;
        public uint isActive;
        public bool hasGameBegun;
        public uint maxPlayers;
    };

    struct LeaveRoomResponse
    {
        public const int LEAVED = 1;
    };

    struct CloseRoomResponse
    {
        public const int CLOSED = 1;
        public const int ERROR_CLOSING = 0;
    };

    struct StartGameResponse
    {
        public const int START_GAME = 1;
        public const int GAME_START_FAIL = 0;
    }

    struct LeaveGameResponse
    {
        public const int LEFT_GAME = 1;
        public const int LEAVE_GAME_FAIL = 0;
    }

    public struct getQuestionResponse
    {
        public const int CONNECTION_PROBLEM = 3;

        public int status;
        public string Question;
        public List<string> Answers;
    }

    public struct GameResultsResponse
    {
        public int status;
        //the indexes matter
        public List<string> Players;
        public List<string> CorrectAnswers;
        public List<string> Avrgs;
    }

}
