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

namespace Client
{
    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Window
    {
        private bool _isClosedByX = true; // we cant know.
        public JoinRoom()
        {
            InitializeComponent();

            //contact server to get rooms.
            refresh();
        }

        private async void refresh()
        {
            List<string> rooms = await Communicator.getRooms();
            foreach (string room in rooms)
            {
                LST_ROOMS.Items.Add(room);
            }
        }

        private async void refresh_Click(object sender, RoutedEventArgs e)
        {
            refresh();
        }

        private void Join_Click(object sender, RoutedEventArgs e)
        {
            if (LST_ROOMS.SelectedItems.Count > 0)
            {
                var selected = LST_ROOMS.SelectedItems[0];
                //move selection to server

                Room room = new Room(selected.ToString());
                room.Show();
                _isClosedByX = false;
                this.Close();
            }
            else
            {
                //stay here, nothing selected.
            }
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
