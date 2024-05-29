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
        public JoinRoom()
        {
            InitializeComponent();

            //contact server to get rooms.
            LST_ROOMS.Items.Add("room1");
            LST_ROOMS.Items.Add("room2");
            LST_ROOMS.Items.Add("room3");

        }

        private void Join_Click(object sender, RoutedEventArgs e)
        {
            if (LST_ROOMS.SelectedItems.Count > 0)
            {
                var selected = LST_ROOMS.SelectedItems[0];
                //move selection to server
                MainMenu men = new MainMenu();
                men.Show();
                this.Close();
            }
            else
            {
                //stay here, nothing selected.
            }
        }
    }
}
