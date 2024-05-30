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

namespace Client
{
    internal class Communicator
    {
        const int HEADER_SIZE = 5;
        const int HEADER_LEN_SIZE = 4;

        const int PORT = 9090;
        const string IP = "127.0.0.1";

        TcpClient _socket;
        StreamReader _in;
        StreamWriter _out;

        string username;

        public Communicator() 
        {
            _socket = new TcpClient();
            IAsyncResult result = _socket.BeginConnect("127.0.0.1", 9090, null, null);

            // Wait 5 seconds for the connection attempt to complete
            result.AsyncWaitHandle.WaitOne(5000);

            if (!_socket.Connected)
            {
                
            }
            else
            {
                // Set up streams for reading and writing
                _in = new StreamReader(_socket.GetStream());
                _out = new StreamWriter(_socket.GetStream());
                _out.AutoFlush = true;
            }
        }

        public void Close()
        {
            if (_socket != null)
            {
                _in.Close();
                _out.Close();
                _socket.Close();
            }
        }

        public bool login(string username, string password)
        {
            int jsonLen = 0;
            string jsonStr = "";
            byte[] ubjsonBytes;
            byte[] lenHeader;
            byte[] fullMsg;
            byte[] resp;
            msgCodes code = msgCodes.LOGIN;

            LoginRequest loginRequest = new LoginRequest()
            {
                username = username,
                password = password
            };
            jsonStr = Newtonsoft.Json.JsonConvert.SerializeObject(loginRequest);
            jsonLen = jsonStr.Length;

            ubjsonBytes = Encoding.UTF8.GetBytes(jsonStr); // Convert json string to byte array.

            //len of json into 4 bytes
            lenHeader = new byte[4];
            lenHeader[0] = (byte)(jsonLen >> 24);
            lenHeader[1] = (byte)(jsonLen >> 16);
            lenHeader[2] = (byte)(jsonLen >> 8);
            lenHeader[3] = (byte)jsonLen;

            //create the full msg
            fullMsg = new byte[jsonLen + HEADER_SIZE];
            fullMsg[0] = (byte)code;
            Array.Copy(lenHeader, fullMsg, HEADER_LEN_SIZE);
            Array.Copy(ubjsonBytes, fullMsg, jsonLen);

            //send to server
            _out.Write(fullMsg);
            _out.Flush();

            //create the stream and reader.
            NetworkStream stream = _socket.GetStream();
            BinaryReader reader = new BinaryReader(stream);

            //receve header.
            byte[] receivedHeader = reader.ReadBytes(HEADER_SIZE);

            //get length from header
            int respLen = BitConverter.ToInt32(receivedHeader, 1);

            //get entire msg
            byte[] rcvdMsg = reader.ReadBytes(respLen);

            reader.Close();
            stream.Close();

            string recvJson = Encoding.UTF8.GetString(rcvdMsg);
            LoginResponse logResp = new LoginResponse();
            logResp = Newtonsoft.Json.JsonConvert.DeserializeObject<LoginResponse>(recvJson);
            if (logResp.status == LoginResponse.LOGIN_SUCCESS)
            {
                //connected successfully
                this.username = username;
                return true;
            }
            else
            {
                return false;
            }
        }

        public void signup(string username, string password, string mail)
        {

        }

        public void createRoom(string roomName, uint maxPlayers, uint questionsNum, double timeForQuestion)
        {

        }

        public void joinRoom(string roomIdentifier)
        {

        }

        public void personalStats(string roomIdentifier)
        {

        }

        public void topStats(string roomIdentifier)
        {

        }

    }
}
