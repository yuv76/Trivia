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
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class statsMenu : Window
    {
        public bool _isClosedByX = true;
        public statsMenu(double left, double top, double width, double height, WindowState windowstate)
        {
            /*
            statistics menu window C'tor.
            in: the window's position (left, top, width, height, windowstate).
            */

            InitializeComponent();
            Left = left;
            Top = top;
            Width = width; 
            Height = height;
            WindowState = windowstate;

            PutName();
        }

        private void top_click(object sender, RoutedEventArgs e)
        {
            /*
            event handler for top statistics click - moves to high scores window.
            in: the sender, the event arguments.
            out: none.
            */

            HighScores sigi = new HighScores(Left, Top, Width, Height, WindowState);
            sigi.Show();
            _isClosedByX = false;
            this.Close();
        }

        private void personal_click(object sender, RoutedEventArgs e)
        {
            /*
            event handler for the personal statistics menu button click - moves to personal statistics window.
            in; the sender, the event's arguments.
            out: none.
            */
            PersonalStats sigi = new PersonalStats(Left, Top, Width, Height, WindowState);
            sigi.Show();
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

        private void back_click(object sender, RoutedEventArgs e)
        {
            /*
            event handler for the back button - returns to main menu.
            in: the sender, the event's arguments.
            out: none.
            */

            MainMenu sigi = new MainMenu(Left, Top, Width, Height, WindowState, "");
            sigi.Show();
            _isClosedByX = false;
            this.Close();
        }

        private void PutName()
        {
            /*
            displays name of connected user in the name textblock.
            in&out: none.
            */

            string temp = "hello " + Communicator.getName();
            name.Text = temp;
        }
    }
}
