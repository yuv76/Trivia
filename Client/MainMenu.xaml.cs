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

        public MainMenu(double left, double top, double width, double height, WindowState windowstate, string error)
        {
            /*
            main menu window C'tor.
            in: the window's position (left, top, width, height, windowstate), error string if there were errors (empty if not).
            */

            InitializeComponent();
            Left = left;
            Top = top;
            Width = width;
            Height = height;
            WindowState = windowstate;

            ERROR.Text = error;

            PutName();
        }

        private void moveToCreateRoom_click(object sender, RoutedEventArgs e)
        {
            /*
            event handler for the create room button - moves to create room window.
            in: the sender (the button), the event's arguments.
            out: none.
            */

            CreateRoom crRoom = new CreateRoom(Left, Top, Width, Height, WindowState);
            crRoom.Show();
            _isClosedByX = false;
            this.Close();
        }

        private void moveToJoinRoom_click(object sender, RoutedEventArgs e)
        {
            /*
            event handler for the join room button - moves to join room window.
            in: the sender (the button), the event's arguments.
            out: none.
            */

            JoinRoom jnRoom = new JoinRoom(Left, Top, Width, Height, WindowState);
            jnRoom.Show();
            _isClosedByX = false;
            this.Close();
        }

        private void moveToStatsMenu_click(object sender, RoutedEventArgs e)
        {
            /*
            event handler for the stats menu button - moves to stats menu window.
            in: the sender (the button), the event's arguments.
            out: none.
            */

            statsMenu statsMen = new statsMenu(Left, Top, Width, Height, WindowState);
            statsMen.Show();
            _isClosedByX = false;
            this.Close();
        }

        private async void exit_clickAsync(object sender, RoutedEventArgs e)
        {
            /*
            event handler for the sign out button - moves to login window (main window).
            in: the sender (the button), the event's arguments.
            out: none.
            */

            int ok = await Communicator.signoutAsync();
            MainWindow log = new MainWindow(Left, Top, Width, Height, WindowState);
            log.Show();
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
                int ok = await Communicator.signoutAsync();
            }
        }

        private void PutName()
        {
            /*
            puts the connected user's username in the name block.
            in&out: none.
            */

            string temp = "Hello " + Communicator.getName();
            name.Text = temp;
        }

        private void moveToAddQuestionm_click(object sender, RoutedEventArgs e)
        {
            /*
            event handler for the stats menu button - moves to stats menu window.
            in: the sender (the button), the event's arguments.
            out: none.
            */

            AddQuestion addQuestion = new AddQuestion(Left, Top, Width, Height, WindowState);
            addQuestion.Show();
            _isClosedByX = false;
            this.Close();
        }
    }
}
