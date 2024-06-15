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
        private int room_id = 0;
        private int total_time;
        private DispatcherTimer _timer;
        private int playernum = 0;
        private string roomname;
        private int totalQ;
        private int timeQ;

        public GameResults(double left, double top, double width, double height, WindowState windowstate, int numOfQuestions, int timeForQuestion, int roomId, int num, string roomName)
        {
            InitializeComponent();

            PutName();
            room_id = roomId;
            total_time = timeForQuestion * numOfQuestions;
            playernum = num;
            totalQ = numOfQuestions;
            timeQ = timeForQuestion;
            roomname = roomName;

            getGameResults();

            _timer = new DispatcherTimer();
            _timer.Interval = TimeSpan.FromSeconds(total_time);
            _timer.Tick += Timer_Tick;
            _timer.Start();

        }
        private async void Timer_Tick(object sender, EventArgs e)
        {
            getGameResults();
            _timer.Stop();
        }

        async void getGameResults()
        {
            int i = 0;
            GameResultsResponse gameResultsResponse = await Communicator.getGameResults();
            for(i = 0; i < gameResultsResponse.Players.Count; i++)
            {
                Players.Items.Add(gameResultsResponse.Players[i] + " - " + gameResultsResponse.CorrectAnswers[i] + " - " + gameResultsResponse.Avrgs[i]);
            }
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
            if (playernum != 0)
            {
                string newName = this.roomname + this.room_id.ToString();
                int id = await Communicator.createRoom(newName, uint.Parse(this.playernum.ToString()), uint.Parse(this.totalQ.ToString()), double.Parse(this.timeQ.ToString()));
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
                string roomId = getRoomIdByName(this.roomname);
                int ok = await Communicator.joinRoom(roomId);
                if (ok == JoinRoomResponse.JOIN_ROOM_SUCCESS)
                {
                    Room room = new Room(Left, Top, Width, Height, WindowState, this.roomname, getRoomIdByName(this.roomname), "0");
                    room.Show();
                    _isClosedByX = false;
                    this.Close();
                }
            }
        }

        private void backMenu_click(object sender, RoutedEventArgs e)
        {
            MainMenu men = new MainMenu(Left, Top, Width, Height, WindowState);
            men.Show();
            _isClosedByX = false;
            this.Close();
        }

        protected override async void OnClosed(EventArgs e)
        {
            if (_isClosedByX)
            {
                int ok = await Communicator.LeaveGame();
                ok = await Communicator.signoutAsync();
            }
        }

        private void PutName()
        {
            string temp = "hello " + Communicator.getName();
            name.Text = temp;
        }
    }
}
