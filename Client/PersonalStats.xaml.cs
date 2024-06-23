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
    /// Interaction logic for PersonalStats.xaml
    /// </summary>
    public partial class PersonalStats : Window
    {
        bool _isClosedByX = true;

        public PersonalStats(double left, double top, double width, double height, WindowState windowstate)
        {
            /*
            personal stats window C'tor.
            in: the window's position (left, top, width, height, windowstate).
            */

            InitializeComponent();
            Left = left;
            Top = top;
            Width = width;
            Height = height;
            WindowState = windowstate;

            PutName();
            PutPersonalScores();
        }

        private async void PutPersonalScores()
        {
            /*
            gets personal statistics for connected user and displays them in the window.
            in&out: none.
            */
            
            List<string> recvdJson = await Communicator.personalStatsAsync();
            if (recvdJson.Count > 0)
            {
                int i = 0;
                foreach (var stat in recvdJson)
                {
                    switch (i)
                    {
                        case 1:
                            correct.Text = stat;
                            break;
                        case 2:
                            total.Text = stat;
                            break;
                        case 3:
                            games.Text = stat;
                            break;
                        case 4:
                            time.Text = stat;
                            break;
                    }

                    i++;
                }
            }
            else
            {
                ERROR.Text = "No stats found.";
            }
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
            event handler to the back button clicked event, goes back to the statistics menu window.
            in: the sender, the event arguments.
            out: none.
            */

            statsMenu sttMen = new statsMenu(Left, Top, Width, Height, WindowState);
            sttMen.Show();
            _isClosedByX = false;
            this.Close();
        }

        private void PutName()
        {
            /*
            displays the connected user's name in the name textBlock.
            in: none,
            out: none.
            */

            string temp = "Hello " + Communicator.getName();
            name.Text = temp;
        }
    }
}
