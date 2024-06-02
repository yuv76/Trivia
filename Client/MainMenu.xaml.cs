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
using static System.Formats.Asn1.AsnWriter;
using System.Xml.Linq;

namespace Client
{
    /// <summary>
    /// Interaction logic for MainMenu.xaml
    /// </summary>
    public partial class MainMenu : Window
    {
        private bool _isClosedByX = true; // we cant know.

        public MainMenu(double left, double top, double width, double height, WindowState windowstate)
        {
            InitializeComponent();
            Left = left;
            Top = top;
            Width = width;
            Height = height;
            WindowState = windowstate;

            PutName();
        }

        private void moveToCreateRoom_click(object sender, RoutedEventArgs e)
        {
            CreateRoom crRoom = new CreateRoom(Left, Top, Width, Height, WindowState);
            crRoom.Show();
            _isClosedByX = false;
            this.Close();
        }

        private void moveToJoinRoom_click(object sender, RoutedEventArgs e)
        {
            JoinRoom jnRoom = new JoinRoom(Left, Top, Width, Height, WindowState);
            jnRoom.Show();
            _isClosedByX = false;
            this.Close();
        }

        private void moveToStatsMenu_click(object sender, RoutedEventArgs e)
        {
            statsMenu statsMen = new statsMenu(Left, Top, Width, Height, WindowState);
            statsMen.Show();
            _isClosedByX = false;
            this.Close();
        }

        private async void exit_clickAsync(object sender, RoutedEventArgs e)
        {
            uint ok = await Communicator.signoutAsync();
            MainWindow log = new MainWindow(Left, Top, Width, Height, WindowState);
            log.Show();
            _isClosedByX = false;
            this.Close();
        }

        protected override async void OnClosed(EventArgs e)
        {
            if(_isClosedByX)
            {
                uint ok = await Communicator.signoutAsync();
            }
        }

        private void PutName()
        {
            string temp = "hello " + Communicator.getName();
            name.Text = temp;
        }
    }
}
