using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.IO;

namespace Client
{
    internal class Communicator
    {
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
                _socket.Close();
            }
        }

        public void login(string username, string password)
        {

            //if login successfully -
            this.username = username;
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
