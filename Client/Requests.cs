using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
        PERSONAL_STATS,
        DISCONNECT,
        CLOSE_ROOM,
        START_GAME,
        GET_ROOM_STATE,
        LEAVE_ROOM,
        LEAVE_GAME,
        GET_QUESTION,
        SUBMIT_ANSWER,
        GET_GAME_RESULTS
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

    struct JoinRoomRequest
    {
        public string roomId { get; set; }
    };

    struct CreateRoomRequest
    {
        public string roomName { get; set; }
        public uint maxUsers { get; set; }
        public uint questionCount { get; set; }
        public double anwerTimeout { get; set; }
    };

    struct GetPlayersInRoomRequest
    {
        public string roomId { get; set; }
    };

    struct SubmitAnswerRequest
    {
        public uint answerId;
    };

}
