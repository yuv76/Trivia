using Pair;
using System;
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

namespace Client
{
    /// <summary>
    /// Interaction logic for Room.xaml
    /// </summary>

    public partial class Room : Window
    {
        private bool _isClosedByX = true;

        public Room(double left, double top, double width, double height, WindowState windowstate, string roomName, string id)
        {
            InitializeComponent();
            Left = left;
            Top = top;
            Width = width;
            Height = height;
            WindowState = windowstate;

            YOU_ARE_IN_ROOM_XXX.Text = "You are in room " + roomName; //can add list of players in the room for now, this might be the wait for game screen.
            getPlayers(id);
        }

        private async void getPlayers(string id)
        {
            List<string> players = await Communicator.getPlayersInRoom(id);

            OWNER.Text = "room owner: " + players[0];
            players.RemoveAt(0);
            foreach (string player in players)
            {
                PLAYERS.Items.Add(player);
            }
            
        }

        private void back_click(object sender, RoutedEventArgs e)
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
                uint ok = await Communicator.signoutAsync();
            }
        }
    }
}
