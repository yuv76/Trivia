using Pair;
using Responses;
using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Threading;
using System.Xml.Linq;
using static System.Runtime.InteropServices.JavaScript.JSType;


namespace Client
{
    /// <summary>
    /// Interaction logic for GameResults.xaml
    /// </summary>
    public partial class GameResults : Window
    {
        private bool _isClosedByX = true;
        private bool _closed = false;

        List<Pair<string, string>> _rooms;
        private int room_id = 0;
        private int total_time;
        private int playernum = 0;
        private string roomname;
        private int totalQ;
        private int timeQ;

        public GameResults(double left, double top, double width, double height, WindowState windowstate, int numOfQuestions, int timeForQuestion, int roomId, int num, string roomName)
        {
            /*
            game results C'tor.
            in: the window's position (left, top, width, height, windowstate).
            */

            InitializeComponent();
            Left = left;
            Top = top;
            Width = width;
            Height = height;
            WindowState = windowstate;

            PutName();
            room_id = roomId;
            total_time = timeForQuestion * numOfQuestions;
            playernum = num;
            totalQ = numOfQuestions;
            timeQ = timeForQuestion;
            roomname = roomName;

            getGameResults();
        }

        private string getWinner(GameResultsResponse response)
        {
            /*
            Gets the game's winner.
            in: the game results response
            out: the name of the winner, or an empty string if there is no winner.
            */
            string winner = "";
            int i = 0;
            int winnerIndex = 0;

            if (response.status == 1 || response.status == 2)
            {
                for (i = 1; i < response.Players.Count; i++)
                {
                    if (int.Parse(response.CorrectAnswers[i]) > int.Parse(response.CorrectAnswers[winnerIndex]))
                    {
                        winnerIndex = i; //update current to temporary winner.
                    }
                    else if (response.CorrectAnswers[i] == response.CorrectAnswers[winnerIndex])
                    {
                        if (double.Parse(response.Avrgs[i]) < double.Parse(response.Avrgs[winnerIndex])) //compare avrgs.
                        {
                            winnerIndex = i;
                        }
                    }
                }
                winner = response.Players[winnerIndex];
            }
            return winner;
        }

        bool allDone(GameResultsResponse res)
        {
            /*
            checks if all players are done with the game.
            in: the game results response.
            out: true if all finished, false otherwise.
            */
            int i = 0;
            for(i = 0; i < res.Players.Count; i++)
            {
                if (double.Parse(res.Avrgs[i]) == -1)
                {
                    return false; // at least one is still playing.
                }
            }
            return true; // if got here, all finished.
        }

        async void getGameResults()
        {
            /*
            gets and displays game's results.
            in: none.
            out: none.
            */

            int i = 0;
            GameResultsResponse gameResultsResponse = await Communicator.getGameResults();
            string winner = getWinner(gameResultsResponse);
            if (gameResultsResponse.status == 1 || gameResultsResponse.status == 2)
            {
                Players.Items.Clear();
                for (i = 0; i < gameResultsResponse.Players.Count; i++)
                {
                    if (double.Parse(gameResultsResponse.Avrgs[i]) == -1)
                    {
                        Players.Items.Add(gameResultsResponse.Players[i] + " - Game still in proresss.");
                    }
                    else
                    { 
                        if (gameResultsResponse.Players[i] == winner && allDone(gameResultsResponse))
                        {
                            Players.Items.Insert(0, "Winner: " + gameResultsResponse.Players[i] + " correct answers: " + gameResultsResponse.CorrectAnswers[i] + " Average answer time: " + gameResultsResponse.Avrgs[i]);
                        }
                        else
                        {
                            Players.Items.Add(gameResultsResponse.Players[i] + " correct answers: " + gameResultsResponse.CorrectAnswers[i] + " Average answer time: " + gameResultsResponse.Avrgs[i]);
                        }
                    }
                }
            }
            //else - final results already arrived, let current results stay.
        }

        private string getRoomIdByName(string roomName)
        {
            foreach (Pair<string, string> room in _rooms)
            {
                if (room.Second == roomName)
                {
                    return room.First;
                }
            }
            return "-1";
        }

        async void backRoom_click(object sender, RoutedEventArgs e)
        {
            await Communicator.LeaveGame();
            List<Pair<string, string>> rooms = await Communicator.getRooms();
            _rooms = rooms;

            string newName = this.roomname + this.room_id.ToString();
            if (playernum != 0)
            {
                int id = await Communicator.createRoom(newName, uint.Parse(this.playernum.ToString()), uint.Parse(this.totalQ.ToString()), int.Parse(this.timeQ.ToString()));
                if (id >= CreateRoomResponse.CREATE_ROOM_SUCESS_ID)
                {
                    Room room = new Room(Left, Top, Width, Height, WindowState, newName, id.ToString(), this.playernum.ToString());
                    room.Show();
                    _isClosedByX = false;
                    this.Close();
                }
            }
            else
            {
                string roomId = getRoomIdByName(newName);
                if (roomId == "-1")
                {
                    //unexisting room, shouldnt happen, do nothing.
                    ERROR.Text = "Error the admin hasnt joined the room yet.";
                }
                else
                {
                    int ok = await Communicator.joinRoom(roomId);
                    if (ok == JoinRoomResponse.JOIN_ROOM_SUCCESS)
                    {
                        Room room = new Room(Left, Top, Width, Height, WindowState, newName, roomId, "0");
                        room.Show();
                        _isClosedByX = false;
                        this.Close();
                    }
                }
            }
        }

        
        private async void refresh_click(object sender, RoutedEventArgs e)
        {
            /*
            event handler for the refresh results button.
            in: the sender, the event arguments.
            out: none.
            */

            getGameResults();
        }

        private async void backMenu_click(object sender, RoutedEventArgs e)
        {
            /*
            event for the back to menu button, returns to the menu.
            in: the sender, the event arguments.
            out: none.
            */

            await Communicator.LeaveGame();

            MainMenu men = new MainMenu(Left, Top, Width, Height, WindowState, "");
            _closed = true;
            men.Show();
            _isClosedByX = false;
            this.Close();
        }

        protected override async void OnClosed(EventArgs e)
        {
            /*
            event handler for closing window, seperates client closing it from closing it to move to another window.
            in: the sender (Button), the event arguments.
            out: none.
            */

            if (_isClosedByX)
            {
                int ok = await Communicator.LeaveGame();
                ok = await Communicator.signoutAsync();
            }
        }

        private void PutName()
        {
            /*
            puts connected user's username in name textBlock.
            in: none.
            out: none.
            */

            string temp = "Hello " + Communicator.getName();
            name.Text = temp;
        }
    }
}
