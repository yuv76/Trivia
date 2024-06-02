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

namespace Client
{
    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Window
    {
        private bool _isClosedByX = true; // we cant know.
        List<Pair<string, string>> _rooms;

        public JoinRoom(double left, double top, double width, double height, WindowState windowstate)
        {
            InitializeComponent();
            Left = left;
            Top = top;   
            Width = width;
            Height = height;
            WindowState = windowstate;

            PutName();
            //contact server to get rooms.
            refresh();
        }

        private async void refresh()
        {
            List<Pair<string, string>> rooms = await Communicator.getRooms();
            LST_ROOMS.Items.Clear();
            foreach (Pair<string, string> room in rooms)
            {
                LST_ROOMS.Items.Add(room.Second);
            }
            _rooms = rooms;
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
                }
                else
                {
                    uint ok = await Communicator.joinRoom(roomId);
                    if(ok == JoinRoomResponse.JOIN_ROOM_SUCCESS)
                    {
                        Room room = new Room(Left, Top, Width, Height, WindowState, selected.ToString(), getRoomIdByName(selected.ToString()));
                        room.Show();
                        _isClosedByX = false;
                        this.Close();
                    }
                    else
                    {
                        //error joining room
                    }
                }
            }
            else
            {
                //stay here, nothing selected.
            }
        }

        private void back_click(object sender, RoutedEventArgs e)
        {
            MainMenu mainMenu = new MainMenu(Left, Top, Width, Height, WindowState);
            mainMenu.Show();
            _isClosedByX = false;
            this.Close();
        }

        protected override async void OnClosed(EventArgs e)
        {
            if (_isClosedByX)
            {
                uint ok = await Communicator.signoutAsync();
            }
        }

        private void PutName()
        {
            string temp = Communicator.getName();
            name.Text = temp;
        }
    }
}
