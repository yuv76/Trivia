using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using Pair;
using Responses;
using System.Windows.Threading;

namespace Client
{
    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Window
    {
        private bool _isClosedByX = true; // we cant know.
        List<Pair<string, string>> _rooms;
        private DispatcherTimer _timer;

        public JoinRoom(double left, double top, double width, double height, WindowState windowstate)
        {
            InitializeComponent();
            Left = left;
            Top = top;   
            Width = width;
            Height = height;
            WindowState = windowstate;

            PutName();

            _timer = new DispatcherTimer();
            _timer.Interval = TimeSpan.FromSeconds(5);
            _timer.Tick += Timer_Tick;
            _timer.Start(); 


            //contact server to get rooms.
            refresh();
        }

        private async void Timer_Tick(object sender, EventArgs e)
        {
            refresh();

            if (LST_ROOMS.SelectedItems.Count > 0)
            {
                string selected = LST_ROOMS.SelectedItems[0].ToString();
                string roomId = getRoomIdByName(selected);
                getPlayers(roomId);
            }
        }

        private async void refresh()
        {
            List<Pair<string, string>> rooms = await Communicator.getRooms();
            LST_ROOMS.Items.Clear();
            if (rooms.Count > 0)
            {
                foreach (Pair<string, string> room in rooms)
                {
                    LST_ROOMS.Items.Add(room.Second);
                }
                _rooms = rooms;
            }
            else
            {
                ERROR.Text = "No Rooms Found.";
            }
        }

        private async void refresh_Click(object sender, RoutedEventArgs e)
        {
            refresh();
        }

        private string getRoomIdByName(string roomName)
        {
            foreach(Pair<string, string> room in _rooms)
            {
                if(room.Second == roomName)
                {
                    return room.First;
                }
            }
            return "-1";
        }

        private async void Join_Click(object sender, RoutedEventArgs e)
        {
            if (LST_ROOMS.SelectedItems.Count > 0)
            {
                string selected = LST_ROOMS.SelectedItems[0].ToString();
                string roomId = getRoomIdByName(selected);
                if(roomId == "-1")
                {
                    //unexisting room, shouldnt happen, do nothing.
                    ERROR.Text = "Error joining room.";
                }
                else
                {
                    int ok = await Communicator.joinRoom(roomId);
                    if(ok == JoinRoomResponse.JOIN_ROOM_SUCCESS)
                    {
                        _timer.Stop();
                        Room room = new Room(Left, Top, Width, Height, WindowState, selected.ToString(), getRoomIdByName(selected.ToString()));
                        room.Show();
                        _isClosedByX = false;
                        this.Close();
                    }
                    else if(ok == JoinRoomResponse.ROOM_FULL)
                    {
                        ERROR.Text = "Room at maximum capacity.";
                    }
                    else if(ok == LoginResponse.LOGIN_F_CONNECTION_ERROR)
                    {
                        //error joining room
                        ERROR.Text = "Connection error.";
                    }
                }
            }
            else
            {
                //stay here, nothing selected.
            }
        }

        private async void getPlayers(string id)
        {
            List<string> players = await Communicator.getPlayersInRoom(id);
            string admin = "";
            if (players.Count > 0)
            {
                admin = players[0];
                if (admin == Communicator.getName())
                {
                    LST_PLAYERS.Items.Add(admin + " - You, Admin");
                }
                else
                {
                    LST_PLAYERS.Items.Add(admin + " - Admin");
                }
                players.RemoveAt(0);
                foreach (string player in players)
                {
                    if (!(player == admin))
                    {
                        if (player == Communicator.getName())
                        {
                            LST_PLAYERS.Items.Add(player + " - You");
                        }
                        else
                        {
                            LST_PLAYERS.Items.Add(player);
                        }
                    }
                }
            }
            else
            {
                ERROR.Text = "Error loading room players.";
            }
        }


        private void back_click(object sender, RoutedEventArgs e)
        {
            _timer.Stop();
            MainMenu mainMenu = new MainMenu(Left, Top, Width, Height, WindowState);
            mainMenu.Show();
            _isClosedByX = false;
            this.Close();
        }

        protected override async void OnClosed(EventArgs e)
        {
            if (_isClosedByX)
            {
                int ok = await Communicator.signoutAsync();
            }
            _timer.Stop();
        }

        private void PutName()
        {
            string temp = "hello " + Communicator.getName();
            name.Text = temp;
        }
    }
}
