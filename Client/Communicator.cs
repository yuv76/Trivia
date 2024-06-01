using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.IO;

using Requests;
using Responses;

using Newtonsoft.Json;
using System.Reflection.PortableExecutable;
using Newtonsoft.Json.Linq;
using System.Windows.Interop;
using System.Text.Json.Nodes;

namespace Client
{
    public class Communicator
    { 
        const int HEADER_SIZE = 5;
        const int HEADER_LEN_SIZE = 4;

        const int PORT = 9090;
        const string IP = "127.0.0.1";

        public static bool _isConnected;

        private  static TcpClient _socket;
        private static IPEndPoint _serverEndPoint;
        private static StreamReader _in;
        private static StreamWriter _out;
        //BinaryReader _reader;
        private static NetworkStream _stream;

        private static string? username;

        public Communicator() 
        {
            try
            {
                _socket = new TcpClient();
                _serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 4242);
                IAsyncResult result = _socket.BeginConnect("127.0.0.1", 9090, null, null);
                //_socket.Connect(_serverEndPoint);
                // Wait 5 seconds for the connection attempt to complete
                result.AsyncWaitHandle.WaitOne(5000);

                if (!_socket.Connected)
                {

                }
                else
                {
                    _stream = _socket.GetStream();
                    // Set up streams for reading and writing
                    _in = new StreamReader(_socket.GetStream());
                    _out = new StreamWriter(_socket.GetStream());
                    _out.AutoFlush = true;
                    _isConnected = true;

                    // _reader = new BinaryReader(_stream, Encoding.UTF8, true);
                }
            }
            catch(Exception ex)
            {
                _isConnected = false;
            }
        }

        public void Close()
        {
            if (_socket != null)
            {
                _in.Close();
                _out.Close();
                //_reader.Close();
                _stream.Close();
                _socket.Close();
            }
        }

        public static async Task<uint> sendToServer(string jsonMsg, msgCodes code)
        {
            int jsonLen = 0;
            byte[] jsonBytes;
            byte[] lenHeader;
            byte[] fullMsg;

            jsonLen = jsonMsg.Length;

            jsonBytes = Encoding.UTF8.GetBytes(jsonMsg); // Convert json string to byte array.

            //len of json into 4 bytes
            lenHeader = new byte[4];
            lenHeader[0] = (byte)(jsonLen >> 24);
            lenHeader[1] = (byte)(jsonLen >> 16);
            lenHeader[2] = (byte)(jsonLen >> 8);
            lenHeader[3] = (byte)jsonLen;

            //create the full msg
            fullMsg = new byte[jsonLen + HEADER_SIZE];
            fullMsg[0] = (byte)code;
            Array.Copy(lenHeader, 0, fullMsg, 1, HEADER_LEN_SIZE);
            Array.Copy(jsonBytes, 0, fullMsg, HEADER_SIZE, jsonLen);
            try
            {
                _stream.Write(fullMsg, 0, fullMsg.Length);
                _stream.Flush();
                return LoginResponse.LOGIN_SUCCESS;
            }
            catch
            {
                return LoginResponse.LOGIN_F_CONNECTION_ERROR;
            }
        }

        public static async Task<JObject> recieveFromServer()
        {
            try
            {
                //receve header.
                byte[] receivedHeader = new byte[HEADER_SIZE];
                _stream.Read(receivedHeader, 0, HEADER_SIZE);

                //put the length part from the header in an array so it will be able to be converted to int, used by little endian so has to reverse order.
                byte[] respLen = new byte[HEADER_LEN_SIZE];
                respLen[0] = (receivedHeader[4]);
                respLen[1] = (receivedHeader[3]);
                respLen[2] = (receivedHeader[2]);
                respLen[3] = (receivedHeader[1]);

                //get length from header
                int respLenInt = BitConverter.ToInt32(respLen, 0);

                //get entire msg
                byte[] rcvdMsg = new byte[respLenInt];
                _stream.Read(rcvdMsg, 0, respLenInt);
                _stream.Flush();

                string recvJson = Encoding.UTF8.GetString(rcvdMsg);
                JObject resp = new JObject();
                resp = Newtonsoft.Json.JsonConvert.DeserializeObject<JObject>(recvJson);

                resp.Add("server_resp_code", Convert.ToInt32(receivedHeader[0]));
                return resp;
            }
            catch
            {
                JObject err = new JObject();
                err.Add("server_resp_code", LoginResponse.LOGIN_F_CONNECTION_ERROR);
                return err;
            }
        }

        public static async Task<uint> loginAsync(string username, string password)
        {
            string jsonStr = "";

            uint sentSuccesfully = 0;
            JObject recvdJson;

            LoginRequest loginRequest = new LoginRequest()
            {
                username = username,
                password = password
            };

            jsonStr = Newtonsoft.Json.JsonConvert.SerializeObject(loginRequest);
            sentSuccesfully = await sendToServer(jsonStr, msgCodes.LOGIN);
            if(sentSuccesfully == LoginResponse.LOGIN_SUCCESS)
            {
                recvdJson = await recieveFromServer();
                if (recvdJson.ContainsKey("server_resp_code") && recvdJson.Value<int>("server_resp_code") == (int)(Requests.msgCodes.LOGIN))
                {
                    if (recvdJson.ContainsKey("status"))
                    {
                        if (recvdJson.Value<int>("status") == LoginResponse.LOGIN_SUCCESS)
                        {
                            //connected successfully
                            Communicator.username = username;
                        }
                        return recvdJson.Value<uint>("status");
                    }
                    else
                    {
                        return recvdJson.Value<uint>("server_resp_code");
                    }
                }
            }
            //else, return unseccess.
            return sentSuccesfully;
        }

        public static async Task<uint> signupAsync(string username, string password, string mail)
        {
            string jsonStr = "";
            uint sentSuccesfully = 0;
            JObject recvdJson;

            SignupRequest signupRequest = new SignupRequest()
            {
                username = username,
                password = password,
                email = mail
            };
            jsonStr = Newtonsoft.Json.JsonConvert.SerializeObject(signupRequest);
            sentSuccesfully = await sendToServer(jsonStr, msgCodes.SIGNUP);

            if (sentSuccesfully == SignupResponse.SIGNUP_SUCCESS)
            {
                recvdJson = await recieveFromServer();
                if (recvdJson.ContainsKey("server_resp_code") && recvdJson.Value<int>("server_resp_code") == (int)(Requests.msgCodes.SIGNUP))
                {
                    if (recvdJson.ContainsKey("status"))
                    {
                        if (recvdJson.Value<int>("status") == SignupResponse.SIGNUP_SUCCESS)
                        {
                            //connected successfully
                            Communicator.username = username;
                        }
                        return recvdJson.Value<uint>("status");
                    }
                    else
                    {
                        return recvdJson.Value<uint>("server_resp_code");
                    }
                }
            }
            //else, return unseccess.
            return sentSuccesfully;
        }

        public static async Task<uint> signoutAsync()
        {
            uint sentSuccesfully = 0;
            JObject recvdJson;

            sentSuccesfully = await sendToServer("", msgCodes.SIGNOUT);

            if (sentSuccesfully == LogoutResponse.LOGOUT_SUCCESS)
            {
                recvdJson = await recieveFromServer();
                if (recvdJson.ContainsKey("server_resp_code") && recvdJson.Value<int>("server_resp_code") == (int)(Requests.msgCodes.SIGNOUT))
                {
                    if (recvdJson.ContainsKey("status"))
                    {
                        return recvdJson.Value<uint>("status");
                    }
                    else
                    {
                        return recvdJson.Value<uint>("server_resp_code");
                    }
                }
            }
            //else, return unseccess.
            return sentSuccesfully;
        }

        public void createRoom(string roomName, uint maxPlayers, uint questionsNum, double timeForQuestion)
        {

        }

        public void joinRoom(string roomIdentifier)
        {

        }

        public static async Task<uint> personalStatsAsync(string roomIdentifier)
        {
            string jsonStr = "";
            uint sentSuccesfully = 0;
            JObject recvdJson;

            PersonalStatsRequest personalStatsRequest = new PersonalStatsRequest()
            {
                username = Communicator.username
            };
            jsonStr = Newtonsoft.Json.JsonConvert.SerializeObject(personalStatsRequest);
            
            sentSuccesfully = await sendToServer(jsonStr, msgCodes.PERSONAL_STATS);

            if (sentSuccesfully == GetPersonalStatsResponse.PERSONAL_STATS_SUCESS)
            {
                recvdJson = await recieveFromServer();
                if (recvdJson.ContainsKey("server_resp_code") && recvdJson.Value<int>("server_resp_code") == (int)(Requests.msgCodes.PERSONAL_STATS))
                {
                    if (recvdJson.ContainsKey("status"))
                    {
                        //get data.
                        return recvdJson.Value<uint>("status");
                    }
                    else
                    {
                        return recvdJson.Value<uint>("server_resp_code");
                    }
                }
            }
            //else, return unseccess.
            return sentSuccesfully;
        }

        public static async Task<List<string>> topStatsAsync()
        {
            List<string> scores = new List<string>();
            uint sentSuccesfully = 0;
            JObject recvdJson;

            sentSuccesfully = await sendToServer("", msgCodes.HIGH_SCORE);

            if (sentSuccesfully == GetHighScoreResponse.HIGH_SCORES_SUCCESS)
            {
                recvdJson = await recieveFromServer();
                if (recvdJson.ContainsKey("server_resp_code") && recvdJson.Value<int>("server_resp_code") == (int)(Requests.msgCodes.HIGH_SCORE))
                {
                    if (recvdJson.Value<uint>("status") == GetHighScoreResponse.HIGH_SCORES_SUCCESS)
                    {
                        if (recvdJson.ContainsKey("statistics"))
                        {
                            foreach (string stat in recvdJson.Value<JToken>("statistics"))
                            {
                                scores.Add(stat);
                            }
                        }
                    }
                }
            }
            //else, return unseccess.
            return scores;
        }

        public static async Task<List<string>> getRooms()
        {
            List<string> rooms = new List<string>();
            uint sentSuccesfully = 0;
            JObject recvdJson;

            sentSuccesfully = await sendToServer("", msgCodes.GET_ROOM);

            if (sentSuccesfully == GetRoomsResponse.GET_ROOMS_SUCCESS)
            {
                recvdJson = await recieveFromServer();
                if (recvdJson.ContainsKey("server_resp_code") && recvdJson.Value<int>("server_resp_code") == (int)(Requests.msgCodes.GET_ROOM))
                {
                    if (recvdJson.ContainsKey("Rooms"))
                    {
                        //get data.
                        foreach (string room in recvdJson.Value<JToken>("Rooms"))
                        {
                            rooms.Add(room);
                        }
                    }
                }
            }
            //else, return unseccess.
            return rooms;
        }
    }
}
